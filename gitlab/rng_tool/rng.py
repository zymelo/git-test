""" 
Frequency
BlockFrequency
CumulativeSums min/max
Runs
LongestRun
Rank
FFT
NonOverlappingTemplate min/max
OverlappingTemplate  
Universal
ApproximateEntropy
RandomExcursions  min/max
RandomExcursionsVariant  min/max
Serial min/max
LinearComplexity 
"""

filename = "D:\\zouyang\\work\\proj_debug\\rng\\uion_0-13_bit\\AlgorithmTesting\\finalAnalysisReport.txt"
para_list = []
txt_list = []
row_list = []
cnt = 0

Frequency_list = []
BlockFrequency_list = []
CumulativeSums_list = []
Runs_list = []
LongestRun_list = []
Rank_list = []
FFT_list = []
NonOverlappingTemplate_list = []
OverlappingTemplate_list = []
Universal_list = []
ApproximateEntropy_list = []
RandomExcursions_list = []
RandomExcursionsVariant_list = []
Serial_list = []
LinearComplexity_list = [] 

with open(filename, "r") as f:
    for line in f.readlines():
        txt_list.append(line)
    while cnt < len(txt_list):
        row_list.clear()
        for char in txt_list[cnt].split():
            row_list.append(char)
            if char == 'Frequency':
                Frequency_list.append(row_list[10])
            elif char == 'BlockFrequency':
                BlockFrequency_list.append(row_list[10])
            elif char == 'CumulativeSums':
                CumulativeSums_list.append(row_list[10])
            elif char == 'Runs':
                Runs_list.append(row_list[10])
            elif char == 'LongestRun':
                LongestRun_list.append(row_list[10])
            elif char == 'Rank':
                Rank_list.append(row_list[10])                
            elif char == 'FFT':
                FFT_list.append(row_list[10])
            elif char == 'NonOverlappingTemplate':
                NonOverlappingTemplate_list.append(row_list[10])
            elif char == 'OverlappingTemplate':
                OverlappingTemplate_list.append(row_list[10])
            elif char == 'Universal':
                Universal_list.append(row_list[10])
            elif char == 'ApproximateEntropy':
                ApproximateEntropy_list.append(row_list[10])
            elif char == 'RandomExcursions':
                RandomExcursions_list.append(row_list[10])
            elif char == 'RandomExcursionsVariant':
                RandomExcursionsVariant_list.append(row_list[10])
            elif char == 'Serial':
                Serial_list.append(row_list[10])
            elif char == 'LinearComplexity':
                LinearComplexity_list.append(row_list[10])                                                                                                                                                 
        cnt = cnt + 1
    #NonOverlappingTemplate_list.sort()
    #print(NonOverlappingTemplate_list)
    print("CumulativeSums max = ", max(CumulativeSums_list))
    print("CumulativeSums min = ", min(CumulativeSums_list))
    print("NonOverlappingTemplate max = ", max(NonOverlappingTemplate_list))
    print("NonOverlappingTemplate min = ", min(NonOverlappingTemplate_list))
    print("RandomExcursions max = ", max(RandomExcursions_list))
    print("RandomExcursions min = ", min(RandomExcursions_list))
    print("RandomExcursionsVariant max = ", max(RandomExcursionsVariant_list))
    print("RandomExcursionsVariant min = ", min(RandomExcursionsVariant_list))
    print("Serial max = ", max(Serial_list))
    print("Serial min = ", min(Serial_list))
    
    
    
