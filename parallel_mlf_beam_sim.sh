#!/bin/bash

StoreDir=/users/wonsang1995/work/mlf-beam-sim_Add_Time/result_many_parent
beamOn=2e4


if [ ! -d ${StoreDir} ]
then
    echo "creating "${StoreDir}
    mkdir -p ${StoreDir}
    mkdir -p ${StoreDir}/log
fi

parallel_root() 
{
    #number=$1
    #echo $number
    try_num=$(seq -f "%05g" $1 $1)
    inputfile=myOutputfile_add_time_beam${beamOn}_TflatX2_n${try_num}.root 
    logfile=myLogfile_add_time_beam${beamOn}_TflatX2_n${try_num}.log
  
    echo "now start: ./mlf_beam_sim -o "${StoreDir}"/"${inputfile}" mac/runBeam.mac"
    ./mlf_beam_sim -o ${StoreDir}/${inputfile} mac/runBeam.mac >> ${StoreDir}/log/${logfile}

}

#for num in {1..10..1}
#do  
    #echo $num
    #parallel_root $num
#done

Count=1
for num in {1..5000..1}
do
    parallel_root $num &
    if [ ${Count} = 250 ]
    then
        Count=1
        wait
    else
        Count=`expr ${Count} + 1`
    fi
done
wait


# merging all file
hadd myOutputfile_add_time_beam${beamOn}_TflatX2_all.root ${StoreDir}/*.root
