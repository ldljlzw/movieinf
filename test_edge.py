import subprocess

edge = 217
subprocess.call(["./netinf", 
        "-i:Flixster/frequent_movie_viewer/FlixCas1000F.txt", 
        "-n:Flixster/frequent_movie_viewer/Soc1000F.txt",
        "-o:Flixster/frequent_movie_viewer/slow_1000F_"+str(edge)+"E_top1_original",
        "-m:1", "-a:1.5", "-e:"+str(edge), "-s:1", "-t:1"])
for i in range(10, 110, 10):
    edge = 21740 * i / 100
    subprocess.call(["./netinf", 
            "-i:Flixster/frequent_movie_viewer/FlixCas1000F.txt", 
            "-n:Flixster/frequent_movie_viewer/Soc1000F.txt",
            "-o:Flixster/frequent_movie_viewer/slow_1000F_"+str(edge)+"E_top1",
            "-m:1", "-a:1.5", "-e:"+str(edge), "-s:1", "-t:1"])

