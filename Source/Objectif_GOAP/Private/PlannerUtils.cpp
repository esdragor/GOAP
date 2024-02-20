// Fill out your copyright notice in the Description page of Project Settings.


#include "PlannerUtils.h"

TArray<TArray<TSubclassOf<UAgentAction>*>*> *UPlannerUtils::allBranches = nullptr;

TArray<TSubclassOf<UAgentAction>*> UPlannerUtils::MakePlanActions(TArray<TSubclassOf<UAgentAction>*>* allActions,
                                                     TArray<EWorldStateEnum>* worldState, TArray<EGoalEnum>* goals)
{
	TArray<TSubclassOf<UAgentAction>*> tree;

	for (int i = 0; i < goals->Num(); ++i)
	{
		if (TryBuildTreeAction(allActions, worldState, (*goals)[i], tree))
		{
			break;
		}
	}

	return tree;
}

bool UPlannerUtils::TryAddingActionWithDesiredGoal(TArray<TSubclassOf<UAgentAction>*>* allActions,
                                                   TArray<EWorldStateEnum>* worldState,
                                                   TArray<EWorldStateEnum> *conditionsForLinking,
                                                   TArray<TSubclassOf<UAgentAction>*>& branch)
{
	TArray<TSubclassOf<UAgentAction>*> actionsWithDesiredGoals;
	for (int i = 0; i < allActions->Num(); ++i)
	{
		// a tester 
		TSubclassOf<UAgentAction>* currentAction = (*allActions)[i];
		TArray<EWorldStateEnum> *worldStateResults = currentAction->GetDefaultObject()->GetResults();
		TArray<EWorldStateEnum> *conditionsToCheck = conditionsForLinking;

		for (int j = 0; j < worldStateResults->Num(); ++j)
		{
			if (conditionsToCheck->Contains((*worldStateResults)[j]))
			{
				conditionsToCheck->Remove((*worldStateResults)[j]);
			}
		}


		if (conditionsToCheck->Num() > 0)
		{
			for (int j = 0; j < worldState->Num(); ++j)
			{
				if (conditionsToCheck->Contains((*worldState)[j]))
				{
					conditionsToCheck->Remove((*worldState)[j]);
				}
			}
		}

		if (conditionsToCheck->Num() > 0)
		{
			continue;
		}
		else
		{
			branch.Add(currentAction);
			if (CheckAutoSuficentCondition(currentAction, worldState))
			{
				allBranches->Add(&branch);
				return true;
				// c'est good :)
			}
			else
			{
				TryAddingActionWithDesiredGoal(allActions, worldState, currentAction->GetDefaultObject()->GetConditions(), branch);
			}
		}
	}
	return false;
}

bool UPlannerUtils::TryBuildTreeAction(TArray<TSubclassOf<UAgentAction>*>* allActions, TArray<EWorldStateEnum>* worldState,
                                       EGoalEnum goal, TArray<TSubclassOf<UAgentAction>*>& tree)
{
	// Iterate on each action
	// Store All actions with return goal == goal, else return false if not found
	// Iterate on each Action with desired goal
	// Create Tree and add it to the tree list, else don't add
	// Iterate on the tree List, if treeSize > 0
	// Get the shortest tree
	// Return the shortest tree
	TArray<TSubclassOf<UAgentAction>*> actionsWithDesiredGoals;
	allBranches = new TArray<TArray<TSubclassOf<UAgentAction>*>*>;
	for (int i = 0; i < allActions->Num(); ++i)
	{
		// a tester 
		TSubclassOf<UAgentAction>* currentAction = (*allActions)[i];
		TArray<EGoalEnum>* goals = currentAction->GetDefaultObject()->GetGoals();

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
		TArray<TSubclassOf<UAgentAction>*>* branch = new TArray<TSubclassOf<UAgentAction>*>();
		branch->Add(actionsWithDesiredGoals[i]);
		if (CheckAutoSuficentCondition(actionsWithDesiredGoals[i], worldState))
		{
			allBranches->Add(branch);
			// :)
		}
		else
		{
			TryAddingActionWithDesiredGoal(allActions, worldState, actionsWithDesiredGoals[i]->GetDefaultObject()->GetConditions(),
			                               *branch);
		}
	}


	tree.Empty();
	return false;
}

bool UPlannerUtils::CheckAutoSuficentCondition(TSubclassOf<UAgentAction>* currentAction, TArray<EWorldStateEnum>* worldState)
{
	TArray<EWorldStateEnum>* conditionToAction = currentAction->GetDefaultObject()->GetConditions();
	TArray<EWorldStateEnum> conditionToActionCopy = *conditionToAction;
	for (int i = 0; i < conditionToAction->Num(); ++i)
	{
		bool isResolvedOneCondition = false;
		for (int j = 0; j < worldState->Num(); ++j)
		{
			if ((*conditionToAction)[i] == (*worldState)[j])
			{
				isResolvedOneCondition = true;
				break;
			}
			if (!isResolvedOneCondition)
				return false; // je relance car une de mes conditions est pas dans le WS
		}
	}
	return true;
}
