// This is the main DLL file.

#include "stdafx.h"

#include "WrapperCE.h"

WrapperCE::EngineCE::EngineCE()
{
	engineCE = new FatigueEngine();
	engineCE->SetGender(Male);
}

WrapperCE::EngineCE::~EngineCE()
{
	delete engineCE;
}

void WrapperCE::EngineCE::Reset()
{
	engineCE->Reset();

}
	
void WrapperCE::EngineCE::SetGender(WrapperCE::InterOp::UserGender gender)
{
	engineCE->SetGender((UserGender)gender);
}

Vector3D WrapperCE::EngineCE::ConvertPV(InterOp::Point3D source)
{
	return Vector3D(source.X, source.Y, source.Z);
}

WrapperCE::InterOp::Vector3D WrapperCE::EngineCE::ConvertVP(Vector3D source)
{
	WrapperCE::InterOp::Vector3D vector3D = WrapperCE::InterOp::Vector3D();
	vector3D.X = source.X;
	vector3D.Y = source.Y;
	vector3D.Z = source.Z;
	return vector3D;
}

WrapperCE::InterOp::FatigueData WrapperCE::EngineCE::ConvertFatigueData(FatigueData fatigueData)
{
	WrapperCE::InterOp::FatigueData interOpData = WrapperCE::InterOp::FatigueData();
	interOpData.TargetArm = (InterOp::Arm)fatigueData.TargetArm;
	interOpData.Theta = fatigueData.Theta;
	interOpData.CenterOfMass = this->ConvertVP(fatigueData.CenterOfMass);
	interOpData.Displacement = this->ConvertVP(fatigueData.Displacement);
	interOpData.Velocity = this->ConvertVP(fatigueData.Velocity);
	interOpData.Acceleration = this->ConvertVP(fatigueData.Acceleration);
	interOpData.InertialTorque = this->ConvertVP(fatigueData.InertialTorque);
	interOpData.AngularAcceleration = fatigueData.AngularAcceleration;
	interOpData.ShoulderTorque = fatigueData.ShoulderTorque;
	interOpData.Endurance = fatigueData.Endurance;
	interOpData.AvgShoulderTorque = fatigueData.AvgShoulderTorque;
	interOpData.ArmStrength = fatigueData.ArmStrength;
	interOpData.AvgArmStrength = fatigueData.AvgArmStrength;
	interOpData.AvgEndurance = fatigueData.AvgEndurance;
	interOpData.ConsumedEndurance = fatigueData.ConsumedEndurance;
	return interOpData;
}

WrapperCE::InterOp::ArmFatigueUpdate WrapperCE::EngineCE::ProcessNewSkeletonData(InterOp::SkeletonData armsData, double deltaTimeInSeconds)
{
	InterOp::ArmFatigueUpdate interOp = InterOp::ArmFatigueUpdate();
	//general.h SkeletonData
	SkeletonData input;
	input.RightShoulderCms =	this->ConvertPV(armsData.RightShoulderCms);
	input.RightElbowCms =			this->ConvertPV(armsData.RightElbowCms);
	input.RightWristCms =			this->ConvertPV(armsData.RightWristCms);
	input.RightHandCms =			this->ConvertPV(armsData.RightHandCms);

	input.LeftShoulderCms =		this->ConvertPV(armsData.LeftShoulderCms);
	input.LeftElbowCms =			this->ConvertPV(armsData.LeftElbowCms);
	input.LeftWristCms =			this->ConvertPV(armsData.LeftWristCms);
	input.LeftHandCms =				this->ConvertPV(armsData.LeftHandCms);

	ArmFatigueUpdate update = engineCE->ProcessNewSkeletonData(input, deltaTimeInSeconds);
	interOp.LeftArm = this-> ConvertFatigueData(update.LeftArm);
	interOp.RightArm = this-> ConvertFatigueData(update.RightArm);

	return interOp;
}
