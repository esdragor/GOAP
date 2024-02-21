// Fill out your copyright notice in the Description page of Project Settings.


#include "PlannerUtils.h"


TArray<TSubclassOf<UAgentAction>> UPlannerUtils::MakePlanActions(TArray<TSubclassOf<UAgentAction>> allActions,
                                                     TArray<EWorldStateEnum>* worldState, TArray<EGoalEnum>* goals)
{
	TArray<TSubclassOf<UAgentAction>> tree;

	for (int i = 0; i < goals->Num(); ++i)
	{
	
		if (TryBuildTreeAction(allActions, worldState, (*goals)[i], tree))
		{
			break;
		}
	}
	return tree;
}

bool UPlannerUtils::TryBuildTreeAction(TArray<TSubclassOf<UAgentAction>> allActions,
	TArray<EWorldStateEnum>* worldState, EGoalEnum goal, TArray<TSubclassOf<UAgentAction>>& branch)
{
	TArray<TSubclassOf<UAgentAction>>* bestBranch = new TArray<TSubclassOf<UAgentAction>>();
	float maxCost = 1000;
	for (int i = 0; i < allActions.Num(); ++i)
	{
		// a tester 
		UAgentAction* currentAction = (allActions)[i]->GetDefaultObject<UAgentAction>();
		TArray<EGoalEnum>* goals = currentAction->GetGoals();
		
		for (int j = 0; j < goals->Num(); ++j)
		{
			if ((*goals)[j] == goal)
			{
				TArray<TSubclassOf<UAgentAction>>* currentBranch = new TArray<TSubclassOf<UAgentAction>>();
				if(TryCreateBranchAction(allActions, worldState, currentAction->GetConditions(),currentBranch, maxCost))
				{
					if(maxCost > currentBranch->Num())
					{
						maxCost = currentBranch->Num();
						bestBranch = currentBranch; 
					}
				}
				break; 
			}
		}
	}
	branch = *bestBranch; 

	return false;
}




bool UPlannerUtils::TryCreateBranchAction(TArray<TSubclassOf<UAgentAction>> allActions,
	TArray<EWorldStateEnum>* worldState, TArray<EWorldStateEnum>* conditions, TArray<TSubclassOf<UAgentAction>>* branch,
	float maxCost)
{
	if(conditions->Num() == 0)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < conditions->Num(); ++i)
		{
			if(worldState->Contains((*conditions)[i]))
			{
				continue;
			}
			TArray<TSubclassOf<UAgentAction>>* bestSubBranch = new TArray<TSubclassOf<UAgentAction>>();
				for (int j = 0; j < allActions.Num(); ++j)
				{
					UAgentAction* currentAction =allActions[j]->GetDefaultObject<UAgentAction>();
					
					if(currentAction->results.Contains((*conditions)[i]))
					{
						branch->Add(allActions[j]);
						TArray<TSubclassOf<UAgentAction>>* newSubBranch = new TArray<TSubclassOf<UAgentAction>>();
						maxCost += 1;
						if(TryCreateBranchAction(allActions, worldState, currentAction->GetConditions(), newSubBranch, maxCost))
						{
							if(maxCost > newSubBranch->Num())
							{
								maxCost = newSubBranch->Num();
								bestSubBranch = newSubBranch; 
							}
						}
						else
						{
							return false;
						}
					}
				}
			for (int z = 0; z < bestSubBranch->Num(); ++z)
			{
				branch->Insert((*bestSubBranch)[z],0);
			}
			
		}
		return true;
	
	}
	
	
}

float UPlannerUtils::GetBranchCost(TArray<TSubclassOf<UAgentAction>> actions)
{
	return 0;
}

/*bool UPlannerUtils::CreateSubBranchesForActionWithDesiredGoal(TArray<TSubclassOf<UAgentAction>> allActions,
                                                   TArray<EWorldStateEnum>* worldState,
                                                   TArray<EWorldStateEnum> *conditionsForLinking,
                                                   TArray<TSubclassOf<UAgentAction>> branch)
{


	//TMap<EWorldStateEnum, TArray<TSubclassOf<UAgentAction>>> *allSubranchesPerCondition


	




	TArray<TSubclassOf<UAgentAction>*> actionsWithDesiredGoals;

	for (int i = 0; i < conditionsForLinking->Num(); ++i)
	{
		EWorldStateEnum condition = (*conditionsForLinking)[i];
		allSubranchesPerCondition->Add(condition, TArray<TArray<TSubclassOf<UAgentAction>>>());
		
	}

	
	for (int i = 0; i < allActions.Num(); ++i)
	{
		// a tester 
		TSubclassOf<UAgentAction> currentAction = (allActions)[i];
		TArray<EWorldStateEnum> *worldStateResults = currentAction->GetDefaultObject<UAgentAction>()->GetResults();
		TArray<EWorldStateEnum> conditionsToCheck = *conditionsForLinking;

		for (int j = 0; j < worldStateResults->Num(); ++j)
		{
			if (conditionsToCheck.Contains((*worldStateResults)[j]))
			{
				conditionsToCheck.Remove((*worldStateResults)[j]);
			}
		}


		if (conditionsToCheck.Num() > 0)
		{
			for (int j = 0; j < worldState->Num(); ++j)
			{
				if (conditionsToCheck.Contains((*worldState)[j]))
				{
					conditionsToCheck.Remove((*worldState)[j]);
				}
			}
		}

		if (conditionsToCheck.Num() > 0)
		{
			continue;
		}
		else
		{
			branch.Add(currentAction);
			if (CheckAutoSuficentCondition(currentAction, worldState))
			{
				allBranches->Add(branch);
				return true;
				// c'est good :)
			}
			else
			{
				TryAddingActionWithDesiredGoal(allActions, worldState, currentAction->GetDefaultObject<UAgentAction>()->GetConditions(), branch);
			}
		}
		
	}
	return false;
}

bool UPlannerUtils::TryBuildTreeAction(TArray<TSubclassOf<UAgentAction>> allActions, TArray<EWorldStateEnum>* worldState,
                                       EGoalEnum goal, TArray<TSubclassOf<UAgentAction>>& tree)
{
	// Iterate on each action
	// Store All actions with return goal == goal, else return false if not found
	// Iterate on each Action with desired goal
	// Create Tree and add it to the tree list, else don't add
	// Iterate on the tree List, if treeSize > 0
	// Get the shortest tree
	// Return the shortest tree
	TSubclassOf<UAgentAction> actionsWithDesiredGoals;
	allBranches = new TArray<TArray<TSubclassOf<UAgentAction>>>;
	for (int i = 0; i < allActions.Num(); ++i)
	{
		// a tester 
		TSubclassOf<UAgentAction> currentAction = (allActions)[i];
		TArray<EGoalEnum>* goals = currentAction->GetDefaultObject<UAgentAction>()->GetGoals();

		for (int j = 0; j < goals->Num(); ++j)
		{
			if ((*goals)[j] == goal)
			{
				actionsWithDesiredGoals.Add(currentAction);
				break;
			}
		}
	}
	if (actionsWithDesiredGoals.Num() < 1)
		return false;


	for (int i = 0; i < actionsWithDesiredGoals.Num(); ++i)
	{
	

		TArray<TSubclassOf<UAgentAction>>* branch = new TArray<TSubclassOf<UAgentAction>>();
		branch->Add(actionsWithDesiredGoals[i]);
		if (CheckAutoSuficentCondition(actionsWithDesiredGoals[i], worldState))
		{
			allBranches->Add(*branch);
			// :)
		}
		else
		{
			CreateSubBranchesForActionWithDesiredGoal(allActions, worldState, actionsWithDesiredGoals[i]->GetDefaultObject<UAgentAction>()->GetConditions(),
			                               *branch);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("allBranches->Num() %d"), allBranches->Num());
	if (allBranches->Num() == 0)
	{
		tree.Empty();
		return false;
	}

tree = allBranches->operator[](0);
	return true;
}
*/
