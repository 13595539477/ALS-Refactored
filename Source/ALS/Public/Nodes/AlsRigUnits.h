#pragma once

#include "RigVMFunctions/RigVMFunction_ControlFlow.h"
#include "RigVMFunctions/Math/RigVMFunction_MathFloat.h"
#include "RigVMFunctions/Simulation/RigVMFunction_SimBase.h"
#include "Units/RigUnit.h"
#include "AlsRigUnits.generated.h"

/**
 * @brief 将浮点值限制在[0,1]范围内
 */
USTRUCT(DisplayName = "Clamp 01", Meta = (Category = "ALS"))
struct ALS_API FAlsRigVMFunction_Clamp01Float : public FRigVMFunction_MathFloatBase
{
	GENERATED_BODY()

public:
	/// 输入值
	UPROPERTY(Meta = (Input))
	float Value{0.0f};

	/// 输出值
	UPROPERTY(Meta = (Output))
	float Result{0.0f};

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};

/**
 * @brief 向量阻尼函数
 */
USTRUCT(DisplayName = "Damper Exact (Vector)", Meta = (Category = "ALS"))
struct ALS_API FAlsRigVMFunction_DamperExactVector : public FRigVMFunction_SimBase
{
	GENERATED_BODY()

public:
	// 目标值
	UPROPERTY(Meta = (Input))
	FVector Target{ForceInit};

	/// HalfLife is the time it takes for the distance to the target to be reduced by half.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "s"))
	float HalfLife{1.0f};

	// 当前值
	UPROPERTY(Transient, Meta = (Output))
	FVector Current{ForceInit};

	// 是否初始化
	UPROPERTY(Transient)
	bool bInitialized{false};

public:
	virtual void Initialize() override;

	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};

/**
 * @brief 旋转阻尼函数
 */
USTRUCT(DisplayName = "Damper Exact (Quaternion)", Meta = (Category = "ALS"))
struct ALS_API FAlsRigVMFunction_DamperExactQuaternion : public FRigVMFunction_SimBase
{
	GENERATED_BODY()

public:
	// 目标值
	UPROPERTY(Meta = (Input))
	FQuat Target{ForceInit};

	/// HalfLife is the time it takes for the distance to the target to be reduced by half.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "s"))
	float HalfLife{1.0f};

	// 当前值
	UPROPERTY(Transient, Meta = (Output))
	FQuat Current{ForceInit};

	// 是否初始化
	UPROPERTY(Transient)
	bool bInitialized{false};

public:
	virtual void Initialize() override;

	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};

///计算极向量, 计算垂直于AC的投影位置和方向。
USTRUCT(DisplayName = "Calculate Pole Vector", Meta = (Category = "ALS", NodeColor = "0.05 0.25 0.05"))
struct ALS_API FAlsRigUnit_CalculatePoleVector : public FRigUnit
{
	GENERATED_BODY()

public:
	// 输入A
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey ItemA;

	// 输入B
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey ItemB;

	// 输入C
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey ItemC;

	// 是否初始化
	UPROPERTY(Meta = (Input))
	bool bInitial{false};

	// 输出成功
	UPROPERTY(Transient, Meta = (Output))
	bool bSuccess{false};

	// 输出B位置
	UPROPERTY(Transient, DisplayName = "Item B Location", Meta = (Output))
	FVector ItemBLocation{ForceInit};

	// 输出B投影位置
	UPROPERTY(Transient, DisplayName = "Item B Projection Location", Meta = (Output))
	FVector ItemBProjectionLocation{ForceInit};

	// 输出极向量方向
	UPROPERTY(Transient, Meta = (Output))
	FVector PoleDirection{FVector::ForwardVector};
	
	UPROPERTY(Transient)
	FCachedRigElement CachedItemA;

	UPROPERTY(Transient)
	FCachedRigElement CachedItemB;

	UPROPERTY(Transient)
	FCachedRigElement CachedItemC;

public:
	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};

/// 是否是游戏世界
USTRUCT(DisplayName = "Is Game World", Meta = (Category = "ALS"))
struct ALS_API FAlsRigVMFunction_IsGameWorld : public FRigVMFunction_ControlFlowBase
{
	GENERATED_BODY()

public:
	/// 输入执行文上下文
	UPROPERTY(Transient, DisplayName = "Execute", Meta = (Input))
	FRigVMExecuteContext ExecuteContext;

	/// 为游戏世界
	UPROPERTY(Transient, Meta = (Output))
	FRigVMExecuteContext True;

	/// 不为游戏世界
	UPROPERTY(Transient, Meta = (Output))
	FRigVMExecuteContext False;

	/// 完成
	UPROPERTY(meta=(Output))
	FRigVMExecuteContext Completed;

	UPROPERTY(Transient, Meta = (Singleton))
	FName BlockToRun;

public:
	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;

	virtual const TArray<FName>& GetControlFlowBlocks_Impl() const override;
};
