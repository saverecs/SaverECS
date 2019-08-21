// TODO: generate the num satate macros automatically

typedef struct{
    double next_Glucose_Infusion;
    double next_Bloodstream_Insulin;
}RETURN_VAL;

typedef struct{
    double state_Plasma_Glucose;
    double state_Interstitial_Insulin;
    double state_Plasma_Insulin;
    double state_Glucose_Infusion;
    double state_Bloodstream_Insulin;
    double state_global_clock;

}INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);

