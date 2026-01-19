// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlacementInputComponent.h"

#include "DebugHelper.h"
#include "Character/ObjectPlacementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"

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
}

void UPlacementInputComponent::BeginPlay()
{
    Super::BeginPlay();
    
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
        EnhancedInputComponent->BindAction(StartPlacingAction, ETriggerEvent::Triggered, 
            this, &UPlacementInputComponent::OnStartPlacing);
        UE_LOG(LogTemp, Warning, TEXT("StartPlacing Action Bound!"));
    }
    
    if (ConfirmPlacementAction)
    {
        EnhancedInputComponent->BindAction(ConfirmPlacementAction, ETriggerEvent::Triggered, 
            this, &UPlacementInputComponent::OnConfirmPlacement);
    }
    
    if (CancelPlacementAction)
    {
        EnhancedInputComponent->BindAction(CancelPlacementAction, ETriggerEvent::Triggered, 
            this, &UPlacementInputComponent::OnCancelPlacement);
    }
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