// Fill out your copyright notice in the Description page of Project Settings.


#include "PlannerUtils.h"

#include "AgentAction.h"

TArray<TSubclassOf<UAgentAction>> UPlannerUtils::MakePlanActions(TArray<TSubclassOf<UAgentAction>> allActions,
                                                                 TArray<EWorldStateEnum>* worldState, TArray<EWorldStateEnum>* goals)
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
	TArray<EWorldStateEnum>* worldState, EWorldStateEnum goal, TArray<TSubclassOf<UAgentAction>>& branch)
{
	TArray<TSubclassOf<UAgentAction>>* bestBranch = new TArray<TSubclassOf<UAgentAction>>();
	float maxCost = 1000;
	for (int i = 0; i < allActions.Num(); ++i)
	{
		// a tester 
		UAgentAction* currentAction = (allActions)[i]->GetDefaultObject<UAgentAction>();
		TArray<EWorldStateEnum>* goals = currentAction->GetResults();
		
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