// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ToonTanksAIController.generated.h"

class APawnTank;

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksAIController : public AAIController
{
	GENERATED_BODY()

private:

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
