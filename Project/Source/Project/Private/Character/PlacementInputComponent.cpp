// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlacementInputComponent.h"

#include "DebugHelper.h"
#include "Character/ObjectPlacementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"

// UPlacementInputComponent::UPlacementInputComponent()
// {
//     PrimaryComponentTick.bCanEverTick = false;
// }
//
// void UPlacementInputComponent::BeginPlay()
// {
//     Super::BeginPlay();
//     
//     AActor* Owner = GetOwner();
//     if (!Owner) return;
//
//     PlacementComponent = Owner->FindComponentByClass<UObjectPlacementComponent>();
//     
//     APawn* Pawn = Cast<APawn>(Owner);
//     if (!Pawn) return;
//     //
//     // // 2. InputComponent 가져와서 바인딩
//     UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent);
//     if (!EnhancedInputComponent) return;
//     
//     if (APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
//     {
//         if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
//         {
//             // DefaultMappingContext는 헤더에 선언한 UInputMappingContext* 변수입니다.
//             // 에디터에서 IMC_Default 같은 에셋을 할당해줘야 합니다.
//             if (PlacementMappingContext)
//             {
//                 Subsystem->AddMappingContext(PlacementMappingContext, 0);
//             }
//         }
//     }
//     
//     if (StartPlacingAction)
//     {
//         EnhancedInputComponent->BindAction(StartPlacingAction, ETriggerEvent::Triggered, 
//             this, &UPlacementInputComponent::OnStartPlacing);
//     }
//     
//     if (ConfirmPlacementAction)
//     {
//         EnhancedInputComponent->BindAction(ConfirmPlacementAction, ETriggerEvent::Triggered, 
//             this, &UPlacementInputComponent::OnConfirmPlacement);
//     }
//     
//     if (CancelPlacementAction)
//     {
//         EnhancedInputComponent->BindAction(CancelPlacementAction, ETriggerEvent::Triggered, 
//             this, &UPlacementInputComponent::OnCancelPlacement);
//     }
// }
//
// // void UPlacementInputComponent::SetupInputComponent(UInputComponent* PlayerInputComponent)
// // {
// //     if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
// //     {
// //         if (StartPlacingAction)
// //         {
// //             EnhancedInputComponent->BindAction(StartPlacingAction, ETriggerEvent::Triggered, 
// //                 this, &UPlacementInputComponent::OnStartPlacing);
// //         }
// //         
// //         if (ConfirmPlacementAction)
// //         {
// //             EnhancedInputComponent->BindAction(ConfirmPlacementAction, ETriggerEvent::Triggered, 
// //                 this, &UPlacementInputComponent::OnConfirmPlacement);
// //         }
// //         
// //         if (CancelPlacementAction)
// //         {
// //             EnhancedInputComponent->BindAction(CancelPlacementAction, ETriggerEvent::Triggered, 
// //                 this, &UPlacementInputComponent::OnCancelPlacement);
// //         }
// //     }
// // }
//
// void UPlacementInputComponent::OnStartPlacing(const FInputActionValue& Value)
// {
//     if (PlacementComponent)
//     {
//         PlacementComponent->StartPlacing();
//     }
// }
//
// void UPlacementInputComponent::OnConfirmPlacement(const FInputActionValue& Value)
// {
//     if (PlacementComponent)
//     {
//         PlacementComponent->ConfirmPlacement();
//     }
// }
//
// void UPlacementInputComponent::OnCancelPlacement(const FInputActionValue& Value)
// {
//     if (PlacementComponent)
//     {
//         PlacementComponent->CancelPlacement();
//     }
// }
UPlacementInputComponent::UPlacementInputComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    
    
    // static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("/Game/_BP/Input/IMC_Placement.IMC_Placement"));
    // if (MappingContextFinder.Succeeded())
    // {
    //     PlacementMappingContext = MappingContextFinder.Object.Get();
    // }

    // static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("/Game/_BP/Input/IMC_Placement.IMC_Placement"));
    //
    // if (MappingContextFinder.Succeeded())
    // {
    //     // 1. 일반적인 방식 (대부분 여기서 해결됨)
    //     PlacementMappingContext = MappingContextFinder.Object.Get();
    // }
    // static TSoftObjectPtr<UInputMappingContext> MappingContext(FSoftObjectPath(TEXT("/Game/_BP/Input/IMC_Placement.IMC_Placement")));
    //
    // PlacementMappingContext = MappingContext.LoadSynchronous();
    
    // PlacementMappingContext = LoadObject<UInputMappingContext>(
    // nullptr,
    // TEXT("/Game/_BP/Input/IMC_Placement.IMC_Placement")
//);

}


void UPlacementInputComponent::OnRotateAction(const FInputActionValue& Value)
{
    if (PlacementComponent)
    {
        float ScrollValue = Value.Get<float>();
        PlacementComponent->RotatePlacement(ScrollValue);
    }
}

void UPlacementInputComponent::OnSelectObject(const FInputActionValue& Value)
{
    if (!PlacementComponent) return;
    
    if (PlacementComponent->IsEditMode()) return;
    
    float CurrentTime = GetWorld()->GetTimeSeconds();
    
    if (CurrentTime - LastClickTime < DoubleClickThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Double Click Detected!"));
        PlacementComponent->TrySelectObject();
    }
    
    LastClickTime = CurrentTime;
}

void UPlacementInputComponent::BeginPlay()
{
    Super::BeginPlay();
    static TSoftObjectPtr<UInputMappingContext> MappingContext(FSoftObjectPath(TEXT("/Game/_BP/Input/IMC_Placement.IMC_Placement")));
    
    PlacementMappingContext = MappingContext.LoadSynchronous();
    
    // static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("/Game/_BP/Input/IMC_Placement.IMC_Placement"));
    // if (MappingContextFinder.Succeeded())
    // {
    //     PlacementMappingContext = MappingContextFinder.Object.Get();
    // }
    
    AActor* Owner = GetOwner();
    if (!Owner) return;

    PlacementComponent = Owner->FindComponentByClass<UObjectPlacementComponent>();
    
    APawn* Pawn = Cast<APawn>(Owner);
    if (!Pawn) return;
    
    // InputComponent 가져오기
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent);
    if (!EnhancedInputComponent) return;
    
    // IMC 추가
    if (APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            if (PlacementMappingContext)
            {
                Subsystem->AddMappingContext(PlacementMappingContext, 1);
                UE_LOG(LogTemp, Warning, TEXT("Mapping Context Added!"));
            }
        }
    }
    
    // 바인딩
    if (StartPlacingAction)
    {
        EnhancedInputComponent->BindAction(StartPlacingAction, ETriggerEvent::Started, 
            this, &UPlacementInputComponent::OnStartPlacing);
        UE_LOG(LogTemp, Warning, TEXT("StartPlacing Action Bound!"));
    }
    
    if (ConfirmPlacementAction)
    {
        EnhancedInputComponent->BindAction(ConfirmPlacementAction, ETriggerEvent::Started, 
            this, &UPlacementInputComponent::OnConfirmPlacement);
    }
    
    if (CancelPlacementAction)
    {
        EnhancedInputComponent->BindAction(CancelPlacementAction, ETriggerEvent::Started, 
            this, &UPlacementInputComponent::OnCancelPlacement);
    }
    
    
    if (RotateAction)
    {
        EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Started, this, &UPlacementInputComponent::OnRotateAction);
    }
    
    if (SelectObjectAction)
    {
        EnhancedInputComponent->BindAction(SelectObjectAction, ETriggerEvent::Started,
            this, &UPlacementInputComponent::OnSelectObject);
    }
}

void UPlacementInputComponent::InitializeComponent()
{
    Super::InitializeComponent();

}

void UPlacementInputComponent::OnStartPlacing(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("B Key Pressed!"));
    
    if (PlacementComponent)
    {
        PlacementComponent->StartPlacing();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlacementComponent is null!"));
    }
}

void UPlacementInputComponent::OnConfirmPlacement(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Left Click!"));
    
    if (!PlacementComponent->IsEditMode()) return;
    
    if (PlacementComponent)
    {
        PlacementComponent->ConfirmPlacement();
    }
}

void UPlacementInputComponent::OnCancelPlacement(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Right Click!"));
    
    if (PlacementComponent)
    {
        PlacementComponent->CancelPlacement();
    }
}