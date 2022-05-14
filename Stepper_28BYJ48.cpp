#include"Stepper_28BYJ48.h"

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

void Stepper_28BYJ48::step( uint64_t _Step_to_Move , uint8_t _Step_Direction ){
    while ( _Step_to_Move > 0 )
    {
        _microtime_now = micros();
        if ( _microtime_now - _StepMotor_LST >= _StepMotor_LBS )
        {
            _StepMotor_LST = _microtime_now;
            if ( _Step_Direction == _clockwise_ )
            {
                _Step_Counter++;
                if ( _Step_Counter == _StepMotor_SPR )
                {
                    _Step_Counter = 0;
                }
            }
            else
            {
                if ( _Step_Counter == 0 )
                {
                    _Step_Counter = _StepMotor_SPR;
                }
                _Step_Counter--;
            }
            _Step_to_Move--;
            _step( _Step_Counter % 4 );
        }
    }
}

void Stepper_28BYJ48::_step( long long _this_step ){
    switch ( _this_step )
    {
        case 0:
            _Motorset( HIGH , LOW , HIGH , LOW );
            break;
        
        case 1:
            _Motorset( LOW , HIGH , HIGH , LOW );
            break;

        case 2:
            _Motorset( LOW , HIGH , LOW , HIGH );
            break;
        
        case 3:
            _Motorset( HIGH , LOW , LOW , HIGH );
            break;
    }
}

void Stepper_28BYJ48::_Motorset( uint8_t _PIN1_Signal , uint8_t _PIN2_Signal , uint8_t _PIN3_Signal , uint8_t _PIN4_Signal ){
    digitalWrite( _PIN1 , _PIN1_Signal );
    digitalWrite( _PIN2 , _PIN2_Signal );
    digitalWrite( _PIN3 , _PIN3_Signal );
    digitalWrite( _PIN4 , _PIN4_Signal );
}