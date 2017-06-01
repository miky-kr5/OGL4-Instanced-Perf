echo "Running Test Suzane 7 6 -9 -7.5 3 -10.5"
echo "**********************************************************************************************" > testResult.txt
echo "Model name:                     models/suzane.obj" >> testResult.txt
echo "Number of horizontal instances: 7" >> testResult.txt
echo "Number of vertical instances:   6" >> testResult.txt
echo "Initial X position:             -9" >> testResult.txt
echo "Initial Y position:             -7.5" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -10.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/suzane.obj" 7 6 -9 -7.5 3 -10.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/suzane.obj" 7 6 -9 -7.5 3 -10.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/suzane.obj" 7 6 -9 -7.5 3 -10.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Goblin 7 6 -9 -7.5 3 -10.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/goblin.obj" >> testResult.txt
echo "Number of horizontal instances: 7" >> testResult.txt
echo "Number of vertical instances:   6" >> testResult.txt
echo "Initial X position:             -9" >> testResult.txt
echo "Initial Y position:             -7.5" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -10.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/goblin.obj" 7 6 -9 -7.5 3 -10.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/goblin.obj" 7 6 -9 -7.5 3 -10.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/goblin.obj" 7 6 -9 -7.5 3 -10.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Train 7 6 -9 -7.5 3 -10.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/train.obj" >> testResult.txt
echo "Number of horizontal instances: 7" >> testResult.txt
echo "Number of vertical instances:   6" >> testResult.txt
echo "Initial X position:             -9" >> testResult.txt
echo "Initial Y position:             -7.5" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -10.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/train.obj" 7 6 -9 -7.5 3 -10.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/train.obj" 7 6 -9 -7.5 3 -10.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/train.obj" 7 6 -9 -7.5 3 -10.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Suzane 14 12 -20 -15 3 -20.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/suzane.obj" >> testResult.txt
echo "Number of horizontal instances: 14" >> testResult.txt
echo "Number of vertical instances:   12" >> testResult.txt
echo "Initial X position:             -20" >> testResult.txt
echo "Initial Y position:             -15" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -20.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/suzane.obj" 14 12 -20 -15 3 -20.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/suzane.obj" 14 12 -20 -15 3 -20.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/suzane.obj" 14 12 -20 -15 3 -20.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Goblin 14 12 -20 -15 3 -20.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/goblin.obj" >> testResult.txt
echo "Number of horizontal instances: 14" >> testResult.txt
echo "Number of vertical instances:   12" >> testResult.txt
echo "Initial X position:             -20" >> testResult.txt
echo "Initial Y position:             -15" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -20.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/goblin.obj" 14 12 -20 -15 3 -20.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/goblin.obj" 14 12 -20 -15 3 -20.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/goblin.obj" 14 12 -20 -15 3 -20.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Train 14 12 -20 -15 3 -20.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/train.obj" >> testResult.txt
echo "Number of horizontal instances: 14" >> testResult.txt
echo "Number of vertical instances:   12" >> testResult.txt
echo "Initial X position:             -20" >> testResult.txt
echo "Initial Y position:             -15" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -20.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/train.obj" 14 12 -20 -15 3 -20.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/train.obj" 14 12 -20 -15 3 -20.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/train.obj" 14 12 -20 -15 3 -20.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Suzane 30 40 -50 -35 3 -20.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/suzane.obj" >> testResult.txt
echo "Number of horizontal instances: 30" >> testResult.txt
echo "Number of vertical instances:   40" >> testResult.txt
echo "Initial X position:             -50" >> testResult.txt
echo "Initial Y position:             -35" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -20.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/suzane.obj" 30 40 -50 -35 3 -20.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/suzane.obj" 30 40 -50 -35 3 -20.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/suzane.obj" 30 40 -50 -35 3 -20.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Goblin 30 40 -50 -35 3 -20.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/goblin.obj" >> testResult.txt
echo "Number of horizontal instances: 30" >> testResult.txt
echo "Number of vertical instances:   40" >> testResult.txt
echo "Initial X position:             -50" >> testResult.txt
echo "Initial Y position:             -35" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -20.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/goblin.obj" 30 40 -50 -35 3 -20.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/goblin.obj" 30 40 -50 -35 3 -20.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/goblin.obj" 30 40 -50 -35 3 -20.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Train 30 40 -50 -35 3 -20.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/train.obj" >> testResult.txt
echo "Number of horizontal instances: 30" >> testResult.txt
echo "Number of vertical instances:   40" >> testResult.txt
echo "Initial X position:             -50" >> testResult.txt
echo "Initial Y position:             -35" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -20.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/train.obj" 30 40 -50 -35 3 -20.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/train.obj" 30 40 -50 -35 3 -20.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/train.obj" 30 40 -50 -35 3 -20.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Suzane 100 100 -100 -100 3 -60.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/suzane.obj" >> testResult.txt
echo "Number of horizontal instances: 7" >> testResult.txt
echo "Number of vertical instances:   6" >> testResult.txt
echo "Initial X position:             -100" >> testResult.txt
echo "Initial Y position:             -100" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -60.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/suzane.obj" 100 100 -100 -100 3 -60.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/suzane.obj" 100 100 -100 -100 3 -60.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/suzane.obj" 100 100 -100 -100 3 -60.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Goblin 100 100 -100 -100 3 -60.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/goblin.obj" >> testResult.txt
echo "Number of horizontal instances: 7" >> testResult.txt
echo "Number of vertical instances:   6" >> testResult.txt
echo "Initial X position:             -100" >> testResult.txt
echo "Initial Y position:             -100" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -60.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/goblin.obj" 100 100 -100 -100 3 -60.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/goblin.obj" 100 100 -100 -100 3 -60.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/goblin.obj" 100 100 -100 -100 3 -60.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "Running Test Train 100 100 -100 -100 3 -60.5"
echo "**********************************************************************************************" >> testResult.txt
echo "Model name:                     models/train.obj" >> testResult.txt
echo "Number of horizontal instances: 7" >> testResult.txt
echo "Number of vertical instances:   6" >> testResult.txt
echo "Initial X position:             -100" >> testResult.txt
echo "Initial Y position:             -100" >> testResult.txt
echo "Inter-model stride:             3" >> testResult.txt
echo "Z camera position:              -60.5" >> testResult.txt
echo "" >> testResult.txt
echo "VAO" >> testResult.txt
./vao "models/train.obj" 100 100 -100 -100 3 -60.5 >> testResult.txt
sleep 3
echo "INSTANCE RENDERING" >> testResult.txt
./instanced "models/train.obj" 100 100 -100 -100 3 -60.5 >> testResult.txt
sleep 3
echo "DISPLAY LIST" >> testResult.txt
./dlist "models/train.obj" 100 100 -100 -100 3 -60.5 >> testResult.txt
echo "**********************************************************************************************" >> testResult.txt
echo " " >> testResult.txt
sleep 3

echo "COMPLETE TEST"
