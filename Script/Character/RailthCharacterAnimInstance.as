class URailthCharacterAnimInstance : UAnimInstance
{

    ARailthCharacter RCharacter;
    UCharacterMovementComponent MovementComponent;

    UPROPERTY()
    bool bIsGrounded;

    UPROPERTY()
    bool bIsJumping;

    UPROPERTY()
    float MoveSpeed;

    UFUNCTION(BlueprintOverride)
    void BlueprintInitializeAnimation()
    {
        RCharacter = Cast<ARailthCharacter>(TryGetPawnOwner());

        if(IsValid(RCharacter))
        {
            MovementComponent = UCharacterMovementComponent::Get(RCharacter);
        }
    }

    UFUNCTION(BlueprintOverride)
    void BlueprintUpdateAnimation(float DeltaTimeX)
    {
        if(!IsValid(RCharacter))
            return;
        
        bIsGrounded = !MovementComponent.IsFalling();
        bIsJumping = RCharacter.GetVelocity().Z > 100;

        FVector2f InputRange = FVector2f(0, 450);
        FVector2f OutputRange = FVector2f(0, 2);
        float GroundVelocity = RCharacter.GetVelocity().DistXY(FVector::ZeroVector);
        MoveSpeed = Math::GetMappedRangeValueClamped(InputRange, OutputRange, GroundVelocity);        
    }
}

