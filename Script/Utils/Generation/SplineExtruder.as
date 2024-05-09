class ASplineExtruder : ARealtimeMeshActor
{

    UPROPERTY(DefaultComponent, RootComponent)
    UStaticMeshComponent MeshComponent;

    UFUNCTION(BlueprintOverride)
    void ConstructionScript()
    {
        
        //MeshComponent.SetStaticMesh(Mesh);
    }

    UFUNCTION(BlueprintOverride)
    void OnGenerateMesh()
    {


    }
}