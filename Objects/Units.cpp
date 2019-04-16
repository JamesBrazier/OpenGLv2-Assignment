// Im very sorry about this file
// Author: sadly me jbr185

#include "Units.h"

namespace Project
{
	void Guard1::updateAnimation(void)
	{
		switch (animationState) {
			case 0: // moving into position 
				if (headSpin < 30) {
					headSpin += animationSpeed;
				}
				if (LforearmLift < 90) {
					LforearmLift += animationSpeed;
				}
				if (LarmRotation < 90) {
					LarmRotation += animationSpeed;
				}
				if (LwristRotation < 90) {
					LwristRotation += animationSpeed;
				}
				LarmLift += animationSpeed;
				if (LarmLift >= 140) {
					animationState = 1;
				}
				break;
			case 1: // scratch forward
				LhandLift += animationSpeed;
				if (LhandLift >= 30) {
					animationState = 2;
				}
				break;
			case 2: // scratch back
				LhandLift -= animationSpeed;
				if (LhandLift <= -10) {
					animationState = 1;
					animationCounterA++;
					if (animationCounterA >= 5) {
						animationCounterA = 0;
						animationState = 3;
					}
				}
				break;
			case 3: // return to base
				if (headSpin > 0) {
					headSpin -= animationSpeed;
				}
				if (LforearmLift > 0) {
					LforearmLift -= animationSpeed;
				}
				if (LarmRotation > 0) {
					LarmRotation -= animationSpeed;
				}
				if (LwristRotation > 0) {
					LwristRotation -= animationSpeed;
				}
				if (LarmLift > 0) {
					LarmLift -= animationSpeed;
					if (LarmLift == 0) {
						animationState = 4;
					}
				}
				LhandLift = 0;
				break;
			case 4: // timeout
				animationCounterA++;
				if (animationCounterA >= 40) {
					animationCounterA = 0;
					animationState = 0;
				}
				break;
		}
	}

	void Guard2::updateAnimation(void)
	{
		switch (animationState) {
			case 0: // move right arm into position
				if (LarmRotation < 0) {
					LarmRotation += animationSpeed;
				}
				if (LarmLift > 0) {
					LarmLift -= animationSpeed;
				}
				if (LforearmLift > 0) {
					LforearmLift -= animationSpeed;
				}
				if (headSpin > -45) {
					headSpin -= animationSpeed;
				}
				RarmRotation -= animationSpeed;
				RarmLift += animationSpeed;
				RforearmLift += animationSpeed;
				if (RarmLift >= 90) {
					
					animationState = 1;
				}
				break;
			case 1: // wave right arm
				RforearmLift += animationSpeed;
				if (RforearmLift >= 120) {
					animationState = 2;
				}
				break;
			case 2: // wave right arm
				RforearmLift -= animationSpeed;
				if (RforearmLift <= 60) {
					animationState = 1;
					animationCounterA++;
					if (animationCounterA >= 4) {
						animationCounterA = 0;
						animationState = 3;
					}
				}
				break;
			case 3: // move back and move left into position
				if (RarmRotation < 0) {
					RarmRotation += animationSpeed;
				}
				if (RarmLift > 0) {
					RarmLift -= animationSpeed;
				}
				if (RforearmLift > 0) {
					RforearmLift -= animationSpeed;
				}
				if (headSpin < 45) {
					headSpin += animationSpeed;
				}
				LarmRotation -= animationSpeed;
				LarmLift += animationSpeed;
				LforearmLift += animationSpeed;
				if (LarmLift >= 90) {

					animationState = 4;
				}
				break;
			case 4: // wave
				LforearmLift += animationSpeed;
				if (LforearmLift >= 120) {
					animationState = 5;
				}
				break;
			case 5: //wave
				LforearmLift -= animationSpeed;
				if (LforearmLift <= 60) {
					animationState = 4;
					animationCounterA++;
					if (animationCounterA >= 4) {
						animationCounterA = 0;
						animationState = 0;
					}
				}
				break;
		}
	}

	void Scout1::updateAnimation(void)
	{
		switch (animationState) {
			case 0:
				if (bodyTilt < 5) {
					bodyTilt += animationSpeed;
				}
				if (LfootLift < 10) {
					LfootLift += animationSpeed;
					RfootLift += animationSpeed;
				}
				if (LlegLift < 20) {
					LlegLift += animationSpeed;
					RlegLift += animationSpeed;
				}
				if (LlowLegLift < 25) {
					LlowLegLift += animationSpeed;
					RlowLegLift += animationSpeed;
				}
				if (headTilt > -10) {
					headTilt -= animationSpeed;
				}
				if (LwristRotation < 90) {
					LwristRotation += animationSpeed;
				}
				if (LshoulderRotation < 70) {
					LshoulderRotation += animationSpeed;
				}
				if (LarmRotation > -60) {
					LarmRotation -= animationSpeed;
				}
				LforearmLift += animationSpeed;
				if (LforearmLift >= 110) {
					animationState = 1;
				}
				break;
			case 1:
				LhandLift -= 1;
				if (LhandLift <= -10) {
					animationState = 2;
				}
				break;
			case 2:
				LhandLift += 1;
				if (LhandLift >= 0) {
					animationState = 1;
					animationCounterA++;
					if (animationCounterA >= 20) {
						animationCounterA = 0;
						animationState = 3;
						LhandLift = 0;
					}
				}
				break;
			case 3:
				bodyTilt -= animationSpeed / 2;
				if (bodyTilt <= 0) {
					bodyTilt = 0;
				}
				LfootLift -= animationSpeed;
				RfootLift -= animationSpeed;
				if (LfootLift <= 0) {
					LfootLift = 0;
					RfootLift = 0;
				}
				LlegLift -= animationSpeed / 2;
				RlegLift -= animationSpeed / 2;
				if (LlegLift <= 0) {
					LlegLift = 0;
					RlegLift = 0;
				}
				LlowLegLift -= animationSpeed / 2;
				RlowLegLift -= animationSpeed / 2;
				if (LlowLegLift <= 0) {
					LlowLegLift = 0;
					RlowLegLift = 0;
				}
				headTilt += animationSpeed / 2;
				if (headTilt >= 0) {
					headTilt = 0;
				}
				LwristRotation -= animationSpeed;
				if (LwristRotation <= 0) {
					LwristRotation = 0;
				}
				LshoulderRotation -= animationSpeed;
				if (LshoulderRotation <= 0) {
					LshoulderRotation = 0;
				}
				LarmRotation += animationSpeed;
				if (LarmRotation >= 0) {
					LarmRotation = 0;
				}
				LforearmLift -= animationSpeed;
				if (LforearmLift <= 0) {
					LforearmLift = 0;
					animationState = 4;
				}
				break;
			case 4:
				animationCounterA++;
				if (animationCounterA >= 60) {
					animationCounterA = 0;
					animationState = 5;
				}
				break;
			case 5:
				if (headSpin > -60) {
					headSpin -= animationSpeed / 2;
				} else {
					animationCounterA++;
					if (animationCounterA >= 5) {
						animationState = 6;
					}
				}
				break;
			case 6:
				headSpin += animationSpeed;
				if (headSpin >= 0) {
					headSpin = 0;
					animationState = 0;
				}
				break;
		}
	}

	void Scout2::updateAnimation(void)
	{
		static char modifier = 1;

		switch (animationState) {
			case 0:
				animationSpeed = 1;
				animationState = 1;
			case 1:
				if (RforearmLift < 30) {
					RforearmLift += animationSpeed;
					LforearmLift += animationSpeed;
				}
				if (RshoulderRotation > -30) {
					RshoulderRotation -= animationSpeed;
					LshoulderRotation += animationSpeed;
				}
				if (LlowLegLift < 30) {
					LlowLegLift += animationSpeed;
					RlowLegLift += animationSpeed;
				}
				if (LfootLift < 10) {
					LfootLift += animationSpeed;
				}
				if (RlegLift > -20) {
					RlegLift -= animationSpeed;
				}
				if (RfootLift < 20) {
					RfootLift += animationSpeed;
				}
				LlegLift += animationSpeed;
				if (LlegLift >= 45) {
					animationState = 2;
				}
				posX += 0.04 * modifier;
				if ((modifier > 0 && posX >= 20) || (modifier < 0 && posX <= -20)) {
					animationState = 3;
					animationSpeed = 3;
				}
				break;
			case 2:
				if (LforearmLift < 30) {
					LforearmLift += animationSpeed;
					RforearmLift += animationSpeed;
				}
				if (LshoulderRotation > -30) {
					LshoulderRotation -= animationSpeed;
					RshoulderRotation += animationSpeed;
				}
				if (RlowLegLift < 30) {
					RlowLegLift += animationSpeed;
					LlowLegLift += animationSpeed;
				}
				if (RfootLift < 10) {
					RfootLift += animationSpeed;
				}
				if (LlegLift > -20) {
					LlegLift -= animationSpeed;
				}
				if (LfootLift < 20) {
					LfootLift += animationSpeed;
				}
				RlegLift += animationSpeed;
				if (RlegLift >= 45) {
					animationState = 1;
				}
				posX += 0.04 * modifier;
				if ((modifier > 0 && posX >= 20) || (modifier < 0 && posX <= -20)) {
					animationState = 3;
					animationSpeed = 3;
				}
				break;
			case 3:
				if (LforearmLift > 0) {
					LforearmLift -= animationSpeed;
				} else if (LforearmLift < 0) {
					LforearmLift += animationSpeed;
				}
				if (RforearmLift > 0) {
					RforearmLift -= animationSpeed;
				} else if (RforearmLift < 0) {
					RforearmLift += animationSpeed;
				}
				if (RshoulderRotation > 0) {
					RshoulderRotation -= animationSpeed;
				} else if (RshoulderRotation < 0) {
					RshoulderRotation += animationSpeed;
				}
				if (LshoulderRotation > 0) {
					LshoulderRotation -= animationSpeed;
				} else if (LshoulderRotation < 0) {
					LshoulderRotation += animationSpeed;
				}
				if (RlowLegLift > 0) {
					RlowLegLift -= animationSpeed;
				} else if (RlowLegLift < 0) {
					RlowLegLift += animationSpeed;
				}
				if (LlowLegLift > 0) {
					LlowLegLift -= animationSpeed;
				} else if (LlowLegLift < 0) {
					LlowLegLift += animationSpeed;
				}
				if (RfootLift > 0) {
					RfootLift -= animationSpeed;
				} else if (RfootLift < 0) {
					RfootLift += animationSpeed;
				}
				if (LfootLift > 0) {
					LfootLift -= animationSpeed;
				} else if (LfootLift < 0) {
					LfootLift += animationSpeed;
				}
				if (LlegLift > 0) {
					LlegLift -= animationSpeed;
				} else if (LlegLift < 0) {
					LlegLift += animationSpeed;
				}
				if (RlegLift > 0) {
					RlegLift -= animationSpeed;
				} else if (RlegLift < 0) {
					RlegLift += animationSpeed;
				}
				if (RlegLift > -animationSpeed && RlegLift < animationSpeed && LlegLift > -animationSpeed && LlegLift < animationSpeed) {
					animationState = 4;
					LforearmLift = 0; RforearmLift = 0;
					RshoulderRotation = 0; LshoulderRotation = 0;
					RlowLegLift = 0; LlowLegLift = 0;
					RfootLift = 0; LfootLift = 0;
					LlegLift = 0; RlegLift = 0;
				}
				break;
			case 4:
				if (RshoulderRotation > -20) {
					RshoulderRotation -= animationSpeed;
				}
				if (RarmRotation < 80) {
					RarmRotation += animationSpeed;
				}
				if (RforearmLift < 80) {
					RforearmLift += animationSpeed;
				}
				if (RhandLift < 5) {
					RhandLift += animationSpeed;
				}
				if (RwristRotation < 80) {
					RwristRotation += animationSpeed;
				}
				RarmLift += animationSpeed;
				if (RarmLift >= 155) {
					animationState = 5;
					animationSpeed = 0.5;
				}
				break;
			case 5:
				headSpin += animationSpeed;
				if (headSpin >= 10) {
					animationState = 6;
				}
				break;
			case 6:
				headSpin -= animationSpeed;
				if (headSpin < animationSpeed && headSpin > -animationSpeed) {
					animationCounterA++;
					if (animationCounterA >= 5) {
						animationCounterA = 0;
						animationState = 7;
						animationSpeed = 3;
					}
				}
				if (headSpin <= -10) {
					animationState = 5;
				}
				break;
			case 7:
				if (RarmRotation > 0) {
					RarmRotation -= animationSpeed;
				} else {
					RarmRotation = 0;
				}
				if (RhandLift > 0) {
					RhandLift -= animationSpeed;
				} else {
					RhandLift = 0;
				}
				if (RwristRotation > 0) {
					RwristRotation -= animationSpeed;
				} else {
					RwristRotation = 0;
				}
				if (RshoulderRotation < 0) {
					RshoulderRotation += animationSpeed;
				} else {
					RshoulderRotation = 0;
				}
				if (RforearmLift > 0) {
					RforearmLift -= animationSpeed;
				} else {
					RforearmLift = 0;
				}
				if (RarmLift > 0) {
					RarmLift -= animationSpeed;
				} else {
					RarmLift = 0;
					animationState = 8;
					modifier = -modifier;
				}
				break;
			case 8:
				orientation += 15 * modifier;
				if (orientation == 90 * modifier) {
					animationSpeed = 1;
					animationState = 1;
				}
				break;
		}
	}
}