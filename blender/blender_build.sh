#!/bin/bash

BLENDER=blender_bin/blender
MODEL_DATA_FOLDER=../src/Debug/data

for file in *.blend; do
     $BLENDER $file -P export.txt  -- 0.2 0.2 0.6 exit
 #   echo ../$file
done

for model in *.model; do
	cp $model $MODEL_DATA_FOLDER/$model
done
