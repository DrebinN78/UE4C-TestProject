// Copyright Epic Games, Inc. All Rights Reserved.

#include "CplusplusCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/BodyInstance.h"
#include "DrawDebugHelpers.h"

//////////////////////////////////////////////////////////////////////////
// ACplusplusCharacter

ACplusplusCharacter::ACplusplusCharacter()
{

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(20.0f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Set our Health
	health = 100.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Create the grab point
	GrabPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Grab Point"));
	GrabPoint->SetupAttachment(RootComponent);
	FVector GPOffset;
	GPOffset.X = 120.0f;
	GPOffset.Y = 0.0f;
	GPOffset.Z = 50.0f;
	GrabPoint->AddLocalOffset(GPOffset);
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACplusplusCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("WriteSave", IE_Pressed, this, &ACplusplusCharacter::WriteSave);

	PlayerInputComponent->BindAction("GrabObject", IE_Pressed, this, &ACplusplusCharacter::GrabObject);
	PlayerInputComponent->BindAction("ReleaseObject", IE_Released, this, &ACplusplusCharacter::ReleaseObject);
	PlayerInputComponent->BindAction("FirePaintGun", IE_Pressed, this, &ACplusplusCharacter::FirePaintGun);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACplusplusCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACplusplusCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACplusplusCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACplusplusCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACplusplusCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACplusplusCharacter::TouchStopped);

	
}

void ACplusplusCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ACplusplusCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ACplusplusCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACplusplusCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACplusplusCharacter::GrabObject()
{
	FHitResult hitresult;
	FVector startVector = GetCapsuleComponent()->GetComponentLocation();
	FVector endVector = GetCapsuleComponent()->GetComponentLocation() + (GetCapsuleComponent()->GetForwardVector() * 300.0f);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(hitresult, startVector, endVector, ECC_Visibility, CollisionParams)) {
		if (hitresult.Actor->IsRootComponentMovable())
		{
			SetGrabbedComponent(hitresult.GetComponent());
			GetGrabbedComponent()->SetEnableGravity(false);
			GetGrabbedComponent()->AttachToComponent(GetGrabPoint(), FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true));
		}
	}
	
}

void ACplusplusCharacter::ReleaseObject(){
	if (GetGrabbedComponent() != nullptr)
	{
		GetGrabbedComponent()->SetEnableGravity(true);
		GetGrabbedComponent()->DetachFromComponent(FDetachmentTransformRules::FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		SetGrabbedComponent(nullptr);
	}
}


void ACplusplusCharacter::FirePaintGun()
{
	FHitResult hitresult;
	FVector startVector = GetCapsuleComponent()->GetComponentLocation();
	FVector endVector = GetCapsuleComponent()->GetComponentLocation() + (GetCapsuleComponent()->GetForwardVector() * 300.0f);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(hitresult, startVector, endVector, ECC_Visibility, CollisionParams)){
		ADecalActor* paintStain = GetWorld()->SpawnActor<ADecalActor>(hitresult.Location, FRotator(90.0f, 0.0f, 0.0f));
		if(paintStain)
		{
			paintStain->SetDecalMaterial(DecalMaterial);
			paintStain->SetLifeSpan(5.0f);
			paintStain->GetDecal()->DecalSize = FVector(75.0f, 75.0f, 75.0f);
		}
	}
	
}

void ACplusplusCharacter::WriteSave()
{
	UMySaveGame* save = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(USaveGame::StaticClass()));
	save->SetSaveData(GetActorLocation(), GetActorRotation(), health);
	UGameplayStatics::SaveGameToSlot(save, TEXT("GameSaveFile"), 0);
}

void ACplusplusCharacter::LoadFromSave(UMySaveGame* save)
{
	SetActorLocation(save->playerLocationData);
	SetActorRotation(save->playerRotationData);
	health = save->playerHealthData;
}

void ACplusplusCharacter::BeginPlay()
{
	Super::BeginPlay();
	spawnPosition = GetActorLocation();
	spawnRotation = GetActorRotation();
	GetController()->Possess(this);
}

void ACplusplusCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (health <= 0.0f)
	{
		Respawn();
	}
}

void ACplusplusCharacter::Respawn()
{
	SetActorLocation(spawnPosition);
	SetActorRotation(spawnRotation);
	health = 100.0f;
}

void ACplusplusCharacter::SetGrabbedComponent(UPrimitiveComponent* Componenttograb)
{
	GrabbedComponent = Componenttograb;
}

void ACplusplusCharacter::MoveForward(float Value)
{
	
	if ((Controller != NULL) && (Value != 0.0f))
	{
		
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACplusplusCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
