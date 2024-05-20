class ARailthCharacter : ACharacter
{
    UPROPERTY(DefaultComponent, VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent Mesh1P;
    
	UPROPERTY(DefaultComponent)
	UEnhancedInputComponent InputComponent;

	UPROPERTY(DefaultComponent)
	USpringArmComponent CameraBoom;
	default CameraBoom.bUsePawnControlRotation = false;
	default CameraBoom.bEnableCameraLag = false;
	default CameraBoom.TargetArmLength = 0;
	default CameraBoom.bDoCollisionTest = false;

    UPROPERTY(DefaultComponent, Attach = CameraBoom, VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) // Attach = CapsuleComponent
	UCameraComponent FirstPersonCameraComponent;

	UPROPERTY(DefaultComponent)
    URailthPlayableComponent RailthPlayableComponent;

	UPROPERTY(Category = Movement)
	float WalkSpeed = 230;

	UPROPERTY(Category = Movement)
	float SprintSpeed = 470;

    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        RailthPlayableComponent.InitializePlayerInput(InputComponent);
		CharacterMovement.MaxWalkSpeed = WalkSpeed;
    }
	
    default CapsuleComponent.SetCapsuleSize(55.f, 96.0f);
	default FirstPersonCameraComponent.SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	default FirstPersonCameraComponent.bUsePawnControlRotation = true;

    default Mesh1P.SetOnlyOwnerSee(true);
	default Mesh1P.bCastDynamicShadow = false;
	default Mesh1P.CastShadow = false;
	default Mesh1P.SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	void TogglePoV()
	{
		bool bToggleFirstPerson = !FirstPersonCameraComponent.bUsePawnControlRotation;
		
		FirstPersonCameraComponent.bUsePawnControlRotation = bToggleFirstPerson;
		
		CameraBoom.bUsePawnControlRotation = !bToggleFirstPerson;
		CameraBoom.TargetArmLength = bToggleFirstPerson ? 0 : 200;
		CameraBoom.bDoCollisionTest = !bToggleFirstPerson;
		CameraBoom.bEnableCameraLag = !bToggleFirstPerson;

	}
}