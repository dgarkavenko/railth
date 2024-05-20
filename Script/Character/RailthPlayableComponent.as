class URailthPlayableComponent : UPawnComponent
{
	UPROPERTY()
	UInputMappingContext CommonContext;
	
	UPROPERTY(BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction MoveAction;
	
	UPROPERTY(BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction MouseLookAction;

	UPROPERTY( BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction JumpAction;

	UPROPERTY( BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction CrouchAction;

	UPROPERTY( BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction SprintAction;

	UPROPERTY( BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction TogglePoVAction;

	APlayerController Controller;
	ARailthCharacter RCharacter;

	void InitializePlayerInput(UEnhancedInputComponent EnhancedInputComponent)
	{
		RCharacter = Cast<ARailthCharacter>(Owner);
		Controller = Cast<APlayerController>(RCharacter.Controller);

		check(IsValid(Controller.LocalPlayer));

		UEnhancedInputLocalPlayerSubsystem InputSubsystem = UEnhancedInputLocalPlayerSubsystem::Get(Controller.LocalPlayer);
		InputSubsystem.ClearAllMappings();
		InputSubsystem.AddMappingContext(CommonContext, 0, FModifyContextOptions());
	
		FEnhancedInputActionHandlerDynamicSignature JumpTriggered;
		JumpTriggered.BindUFunction(this, n"JumpTriggered");
		EnhancedInputComponent.BindAction(JumpAction, ETriggerEvent::Triggered, JumpTriggered);
		
		FEnhancedInputActionHandlerDynamicSignature JumpCompleted;
		JumpCompleted.BindUFunction(this, n"JumpCompleted");
		EnhancedInputComponent.BindAction(JumpAction, ETriggerEvent::Completed, JumpCompleted);

		FEnhancedInputActionHandlerDynamicSignature Move;
		Move.BindUFunction(this, n"Move");
		EnhancedInputComponent.BindAction(MoveAction, ETriggerEvent::Triggered, Move);

		FEnhancedInputActionHandlerDynamicSignature Look;
		Look.BindUFunction(this, n"Look");
		EnhancedInputComponent.BindAction(MouseLookAction, ETriggerEvent::Triggered, Look);

		FEnhancedInputActionHandlerDynamicSignature PoV;
		PoV.BindUFunction(this, n"TogglePoV");
		EnhancedInputComponent.BindAction(TogglePoVAction, ETriggerEvent::Completed, PoV);

		if(IsValid(CrouchAction))
		{
			FEnhancedInputActionHandlerDynamicSignature Crouch;
			Crouch.BindUFunction(this, n"Crouch");
			EnhancedInputComponent.BindAction(CrouchAction, ETriggerEvent::Triggered, Crouch);
		}

		if(IsValid(SprintAction))
		{
			FEnhancedInputActionHandlerDynamicSignature SprintTriggered;
			SprintTriggered.BindUFunction(this, n"SprintTriggered");
			EnhancedInputComponent.BindAction(SprintAction, ETriggerEvent::Triggered, SprintTriggered);

			FEnhancedInputActionHandlerDynamicSignature SprintReleased;
			SprintReleased.BindUFunction(this, n"SprintReleased");
			EnhancedInputComponent.BindAction(SprintAction, ETriggerEvent::Completed, SprintReleased);
		}
	}

	UFUNCTION()
	void TogglePoV(FInputActionValue ActionValue, float32 ElapsedTime, float32 TriggeredTime, const UInputAction SourceAction)
	{
		RCharacter.TogglePoV();
	}


	UFUNCTION(BlueprintCallable)
	void JumpTriggered(FInputActionValue ActionValue, float32 ElapsedTime, float32 TriggeredTime, const UInputAction SourceAction)
	{
		ACharacter Character = Cast<ACharacter>(Owner);
		if (IsValid(Character))
		{
			if(Character.CanJump())
			{
				Character.UnCrouch();
				Character.Jump();
			}
		}
	}

	UFUNCTION(BlueprintCallable)
	void JumpCompleted(FInputActionValue ActionValue, float32 ElapsedTime, float32 TriggeredTime, const UInputAction SourceAction)
	{
		
	}

	UFUNCTION()
	void Crouch(const FInputActionValue Value, float32 ElapsedTime, float32 TriggeredTime, const UInputAction SourceAction)
	{
		if (RCharacter.bIsCrouched)
		{
			RCharacter.UnCrouch();
		}
		else
		{
			RCharacter.Crouch();
		}
	}

	UFUNCTION()
	void SprintTriggered(const FInputActionValue Value, float32 ElapsedTime, float32 TriggeredTime, const UInputAction SourceAction)
	{
		//if(CanSprint())
		RCharacter.UnCrouch();
		UCharacterMovementComponent::Get(RCharacter).MaxWalkSpeed = RCharacter.SprintSpeed;
	}

	UFUNCTION()
	void SprintReleased(const FInputActionValue Value, float32 ElapsedTime, float32 TriggeredTime, const UInputAction SourceAction)
	{	
		UCharacterMovementComponent::Get(RCharacter).MaxWalkSpeed = RCharacter.WalkSpeed;
	}


	UFUNCTION()
	void Move(const FInputActionValue Value, float32 ElapsedTime, float32 TriggeredTime, const UInputAction SourceAction)
	{
		FVector2D MovementVector = Value.Axis2D;

		if (Controller != nullptr)
		{
			RCharacter.AddMovementInput(RCharacter.GetActorForwardVector(), MovementVector.Y);
			RCharacter.AddMovementInput(RCharacter.GetActorRightVector(), MovementVector.X);
		}
	}

	UFUNCTION()
	void Look(const FInputActionValue Value, float32 ElapsedTime, float32 TriggeredTime, const UInputAction SourceAction)
	{
		FVector2D LookAxisVector = Value.Axis2D;

		if (Controller != nullptr)
		{
			RCharacter.AddControllerYawInput(LookAxisVector.X);
			RCharacter.AddControllerPitchInput(LookAxisVector.Y);
		}
	}
}