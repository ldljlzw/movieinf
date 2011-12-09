import subprocess

#subprocess.call(["ls", "-l"])
for i in range(1,2):
    subprocess.call(["./netinf", 
            "-i:Flixster/frequent_movie_viewer/FlixCas1000F.txt", 
            " -n:Flixster/frequent_movie_viewer/Shared400MV.csv",
            "-o:Flixster/frequent_movie_viewer/1000F_21740E_top"+str(i),
            "-m:1", "-a:1.5", "-e:21740", "-s:4", "-t:"+str(i)])


#./netinf -i:Flixster/frequent_movie_viewer/FlixCas1000F.txt -n:Flixster/frequent_movie_viewer/Shared400MV.csv -o:Flixster/frequent_movie_viewer/1000F_21740E_top1 -m:1 -a:1.5 -e:21740 -s:4 -t:1

