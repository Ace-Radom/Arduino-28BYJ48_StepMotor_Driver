#ifndef _STEPPER_28BYJ48_H_
#define _STEPPER_28BYJ48_H_

#define _clockwise_ 0x00
#define _anticlockwise_ 0x01

class Stepper_28BYJ48{
    public:
        Stepper_28BYJ48( uint64_t _StepNUM_per_Rotation , uint16_t _StepMotor_PIN1 , uint16_t _StepMotor_PIN2 , uint16_t _StepMotor_PIN3 , uint16_t _StepMotor_PIN4 );
        void setSpeed( uint32_t _Speed );
        void step( long long _Step_to_Move );
        void steptime( uint64_t _Milliseconds_to_Move , uint8_t _Step_Direction );
        void steptime_milli( uint64_t _Milliseconds_to_Move , uint8_t _Step_Direction );
        void steptime_micro( uint64_t _Microseconds_to_Move , uint8_t _Step_Direction );
        void reset();

    private:
        uint64_t _StepMotor_SPR;  /* StepNUM per Rotation */
        uint16_t _PIN1;
        uint16_t _PIN2;
        uint16_t _PIN3;
        uint16_t _PIN4;

        uint64_t _Step_Counter;  /* show which step stays the motor now */
        uint64_t _StepMotor_LBS;  /* Latency between Steps (in microseconds) */
        uint64_t _StepMotor_LST;  /* Last Step's Time (in microseconds) */
        
        void step( uint64_t _Step_to_Move , uint8_t _Step_Direction );
        void _step( long long _this_step );
        void _Motorset( uint8_t _PIN1_Signal , uint8_t _PIN2_Signal , uint8_t _PIN3_Signal , uint8_t _PIN4_Signal );
};

#endif