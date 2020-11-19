// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "CplusplusCharacter.generated.h"

UCLASS(config=Game)
class ACplusplusCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Point where grabbed objects are stored*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* GrabPoint;
public:
	ACplusplusCharacter();
 
	UPrimitiveComponent* GrabbedComponent;

	UPROPERTY(VisibleAnywhere, Category = Character)
	float health;

	UPROPERTY(VisibleAnywhere, Category = Character)
	FVector spawnPosition;

	UPROPERTY(VisibleAnywhere, Category = Character)
	FRotator spawnRotation;

	UPROPERTY(EditAnywhere, Category = Character)
	UMaterialInstance* DecalMaterial;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable)
	void GrabObject();

	UFUNCTION(BlueprintCallable)
	void ReleaseObject();

	UFUNCTION(BlueprintCallable)
	void FirePaintGun();

	UFUNCTION(BlueprintCallable)
	void Respawn();

	void SetGrabbedComponent(UPrimitiveComponent* Componenttograb);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns Grab Point subobject **/
	FORCEINLINE class USceneComponent* GetGrabPoint() const { return GrabPoint; }
	/** Returns Grabbed Component**/
	FORCEINLINE class UPrimitiveComponent* GetGrabbedComponent() const { return GrabbedComponent; }
};

