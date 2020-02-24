system=EMB


mkdir benchmarks/$system/outputs/
echo ./SaVerECS -g "benchmarks/$system/$system.cfg" --plant-file "benchmarks/$system/$system.ha" --controller-file "benchmarks/$system/$system.c" -o "benchmarks/$system/outputs/$system >benchmarks/$system/outputs/$system.log"
./SaVerECS -g "benchmarks/$system/$system.cfg" --plant-file "benchmarks/$system/$system.ha" --controller-file "benchmarks/$system/$system.c" -o "benchmarks/$system/outputs/$system" >benchmarks/$system/outputs/$system.log &



#########################################################################################################################################################################################################################################
#./SaVerECS -m 100 -t 0.2 -r 0.1 -d 0.001 -u 70 -l 8 --time-horizon 3 --goal "temperature<52" --plant-file "benchmarks/thermostat/thermostat.ha" --controller-file "benchmarks/thermostat/thermostat.c" -o outputs/thermostat

#./SaVerECS -m 100 -t 0.02 -r 0.01 -d 0.001 -u 50 -l 1 --time-horizon 3 --goal "i<=1.2 && i>= 1.0 && angVal>=10 && angVal<=11" --plant-file "benchmarks/dcmotor/dcmotor.ha" --controller-file "benchmarks/dcmotor/dcmotor.c" -o outputs/dcmotor # check u-value not stopping

#./SaVerECS -m 100 -t 0.05 -r 0.05 -d 0.001 -u 20 -l 1 --time-horizon 3 --goal "gt>1" --plant-file "benchmarks/doubleIntegrator/doubleintg.ha" --controller-file "benchmarks/doubleIntegrator/doubleintg.c" -o outputs/doubleintg				# optimized SSA Working 

#./SaVerECS -m 100 -t 0.05 -r 0.05 -d 0.001 -u 20 -l 1 --time-horizon 3 --goal "gt>1" --plant-file "benchmarks/doubleIntegrator/doubleintg.ha" --controller-file "benchmarks/doubleIntegrator/doubleintg.c" -o outputs/doubleintg				# optimized SSA Working 

#./SaVerECS -m 1000 -t 0.1 -r 0.01 -d 0.001 -u 20 -l 1 --time-horizon 3 --goal "shutdown=1" --plant-file "benchmarks/nuclearReactor/nuclearReactor.ha" --controller-file "benchmarks/nuclearReactor/nuclearReactor.c" -o outputs/nuclearReactor --precision 0.1 --noise-params "tempreture:[0.2,0.3]=>[7,19] & c1:[0.4,0.6]=>[77,77]" 

#./SaVerECS -m 1000 -t 0.001 -r 0.001 -d 0.001 -u 5 -l 1 --time-horizon 1 --goal "gt>0.004" --plant-file "benchmarks/EMB/EMB.ha" --controller-file "benchmarks/EMB/EMB.c" -o outputs/EMB				



#Powertrain Benchmark:

#Controller Model with Complex code
#./SaVerECS -m 1000 -t 0.01 -r 0.001 -d 0.001 -u 3 -l 1 --time-horizon 1 --goal "p_airbyfuel_meas>15" --plant-file "benchmarks/powerTrain/powertrain.ha" --controller-file "benchmarks/powerTrain/afc.c" -o outputs/powertrain

#Controller Model with Simplifed code
#./SaVerECS -m 100 -t 0.01 -r 0.01 -d 0.01 -u 30 -l 1 --time-horizon 100 --goal "p_airbyfuel_meas>15" --plant-file "benchmarks/powerTrainSimple/powertrain.ha" --controller-file "benchmarks/powerTrainSimple/afc_simple.c" -o outputs/powerTrainSimple

# with config file:

#./SaVerECS -g "benchmarks/thermostat/thermostat.cfg" --plant-file "benchmarks/thermostat/thermostat.ha" --controller-file "benchmarks/thermostat/thermostat.c" -o outputs/thermostat
#./SaVerECS -g "benchmarks/powerTrainSimple/powertrain.cfg"  --plant-file "benchmarks/powerTrainSimple/powertrain.ha" --controller-file "benchmarks/powerTrainSimple/afc_simple.c" -o outputs/powerTrainSimple
#./SaVerECS -g "benchmarks/powerTrain/powertrain.cfg"  --plant-file "benchmarks/powerTrain/powertrain.ha" --controller-file "benchmarks/powerTrainSimple/afc.c" -o outputs/powerTrain
#./SaVerECS -g "benchmarks/GlycemicControl/glecemicControl.cfg"  --plant-file "benchmarks/GlycemicControl/glecemicControl.ha" --controller-file "benchmarks/GlycemicControl/controller.c" -o outputs/GlycemicControl
#./SaVerECS -g "benchmarks/doubleIntegrator/doubleintg.cfg"  --plant-file "benchmarks/doubleIntegrator/doubleintg.ha" --controller-file "benchmarks/doubleIntegrator/doubleintg.c" -o outputs/doubleIntegrator

#small benchmark Model

#./SaVerECS -g "benchmarks/smallBenchmark/smallBenchmark.cfg"  --plant-file "benchmarks/smallBenchmark/smallBenchmark.ha" --controller-file "benchmarks/smallBenchmark/smallBenchmark.c" -o outputs/smallBenchmark

# try lyapunov theory
#./SaVerECS -g "benchmarks/smallBenchmarkLyap/smallBenchmarkLyap.cfg"  --plant-file "benchmarks/smallBenchmarkLyap/smallBenchmarkLyap.ha" --controller-file "benchmarks/smallBenchmarkLyap/smallBenchmarkLyap.c" -o outputs/smallBenchmarkLyap

#./SaVerECS -g "benchmarks/anotherBenchmarkLyap/anotherBenchmarkLyap.cfg"  --plant-file "benchmarks/anotherBenchmarkLyap/anotherBenchmarkLyap.ha" --controller-file "benchmarks/anotherBenchmarkLyap/anotherBenchmarkLyap.c" -o outputs/anotherBenchmarkLyap

#################################################################################################

