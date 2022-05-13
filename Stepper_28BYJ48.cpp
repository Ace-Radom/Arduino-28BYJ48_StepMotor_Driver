#include"Stepper_28BYJ48.h"
#include<Arduino.h>

/* set the number of steps and four pins in use */
Stepper_28BYJ48::Stepper_28BYJ48( uint64_t _StepNUM_per_Rotation , uint16_t _StepMotor_PIN1 , uint16_t _StepMotor_PIN2 , uint16_t _StepMotor_PIN3 , uint16_t _StepMotor_PIN4 ){
    _StepMotor_SPR = _StepNUM_per_Rotation;
    _PIN1 = _StepMotor_PIN1;
    _PIN2 = _StepMotor_PIN2;
    _PIN3 = _StepMotor_PIN3;
    _PIN4 = _StepMotor_PIN4;
    pinMode( _PIN1 , OUTPUT );
    pinMode( _PIN2 , OUTPUT );
    pinMode( _PIN3 , OUTPUT );
    pinMode( _PIN4 , OUTPUT );
    _Step_Counter = 0;
    _StepMotor_LST = 0;
}

/* 
 * set the speed of the step motor
 * set how many rotation the motor rotates in one minute
*/
void Stepper_28BYJ48::setSpeed( uint32_t _Speed ){
    _StepMotor_LBS = 60LL * 1000LL * 1000LL / _StepMotor_SPR / _Speed;
}

/* rotate the step motor in steps */
void Stepper_28BYJ48::step( long long _Step_to_Move ){
    uint8_t _direction = ( _Step_to_Move > 0 ) ? _clockwise_ : _anticlockwise_;
    step( abs( _Step_to_Move ) , _direction );
}

/* rotate the step motor in milliseconds */
void Stepper_28BYJ48::steptime( uint64_t _Milliseconds_to_Move , uint8_t _Step_Direction ){
    step( _Milliseconds_to_Move * 1000LL / _StepMotor_LBS , _Step_Direction );
}

/* rotate the step motor in milliseconds */
void Stepper_28BYJ48::steptime_milli( uint64_t _Milliseconds_to_Move , uint8_t _Step_Direction ){
    step( _Milliseconds_to_Move * 1000LL / _StepMotor_LBS , _Step_Direction );
}

/* rotate the step motor in microseconds */
void Stepper_28BYJ48::steptime_micro( uint64_t _Microseconds_to_Move , uint8_t _Step_Direction ){
    step( _Microseconds_to_Move / _StepMotor_LBS , _Step_Direction );
}

/* reset the step motor to the beginning position of the program */
void Stepper_28BYJ48::reset(){
    if ( _Step_Counter == 0 || _Step_Counter == _StepMotor_SPR )
    {
        return;
    }
    ( _Step_Counter >= ( _StepMotor_SPR / 2 ) ) ? step( _StepMotor_SPR - _Step_Counter , _clockwise_ )
                                                : step( _Step_Counter , _anticlockwise_ );
}