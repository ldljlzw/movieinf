import subprocess

for i in range(1,21):
    subprocess.call(["./netinf", 
            "-i:Flixster/frequent_movie_viewer/FlixCas1000F.txt", 
            "-n:Flixster/frequent_movie_viewer/Soc1000F.txt",
            "-o:Flixster/frequent_movie_viewer/Original_1000F_21740E_top"+str(i),
            "-m:1", "-a:1.5", "-e:21740", "-s:4", "-t:"+str(i)])
#edge = 217
#subprocess.call(["./netinf", 
#        "-i:Flixster/frequent_movie_viewer/FlixCas1000F.txt", 
#        "-n:Flixster/frequent_movie_viewer/Shared400MV.csv",
#        "-o:Flixster/frequent_movie_viewer/1000F_"+str(edge)+"E_top10",
#        "-m:1", "-a:1.5", "-e:"+str(edge), "-s:4", "-t:10"])
#for i in range(5, 305, 5):
#    edge = 21740 * i / 100
#    subprocess.call(["./netinf", 
#            "-i:Flixster/frequent_movie_viewer/FlixCas1000F.txt", 
#            "-n:Flixster/frequent_movie_viewer/Shared400MV.csv",
#            "-o:Flixster/frequent_movie_viewer/1000F_"+str(edge)+"E_top10",
#            "-m:1", "-a:1.5", "-e:"+str(edge), "-s:4", "-t:10"])

