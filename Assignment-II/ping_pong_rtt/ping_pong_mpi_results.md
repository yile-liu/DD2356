# Dardel 1

```shell
salloc -N 2 -n 2 --ntasks-per-node=1 -p shared -A edu26.DD2356 -t 00:10:00
cc ping_pong_mpi.c -o ping_pong_mpi
srun ./ping_pong_mpi
```

Size: 4 Bytes, RTT: 4.203183 microseconds
Size: 8 Bytes, RTT: 4.154083 microseconds
Size: 16 Bytes, RTT: 4.508881 microseconds
Size: 32 Bytes, RTT: 4.178336 microseconds
Size: 64 Bytes, RTT: 4.189856 microseconds
Size: 128 Bytes, RTT: 5.842411 microseconds
Size: 256 Bytes, RTT: 5.747157 microseconds
Size: 512 Bytes, RTT: 5.767160 microseconds
Size: 1024 Bytes, RTT: 5.946087 microseconds
Size: 2048 Bytes, RTT: 6.271918 microseconds
Size: 4096 Bytes, RTT: 6.761526 microseconds
Size: 8192 Bytes, RTT: 7.003836 microseconds
Size: 16384 Bytes, RTT: 7.893823 microseconds
Size: 32768 Bytes, RTT: 13.714076 microseconds
Size: 65536 Bytes, RTT: 15.897554 microseconds
Size: 131072 Bytes, RTT: 21.639975 microseconds
Size: 262144 Bytes, RTT: 33.128966 microseconds
Size: 524288 Bytes, RTT: 59.757531 microseconds
Size: 1048576 Bytes, RTT: 110.087198 microseconds
Size: 2097152 Bytes, RTT: 205.358038 microseconds
Size: 4194304 Bytes, RTT: 395.159736 microseconds

# School Cluster 1

```shell
conda install -c conda-forge openmpi
mpicc ping_pong_mpi.c -o ping_pong_mpi
mpirun -n 2 ping_pong_mpi
```

Size: 4 Bytes, RTT: 0.699968 microseconds
Size: 8 Bytes, RTT: 0.678102 microseconds
Size: 16 Bytes, RTT: 0.904878 microseconds
Size: 32 Bytes, RTT: 0.899877 microseconds
Size: 64 Bytes, RTT: 1.043154 microseconds
Size: 128 Bytes, RTT: 0.954100 microseconds
Size: 256 Bytes, RTT: 1.080875 microseconds
Size: 512 Bytes, RTT: 1.389944 microseconds
Size: 1024 Bytes, RTT: 1.570854 microseconds
Size: 2048 Bytes, RTT: 2.049346 microseconds
Size: 4096 Bytes, RTT: 4.946817 microseconds
Size: 8192 Bytes, RTT: 6.853843 microseconds
Size: 16384 Bytes, RTT: 10.298664 microseconds
Size: 32768 Bytes, RTT: 17.449091 microseconds
Size: 65536 Bytes, RTT: 31.174280 microseconds
Size: 131072 Bytes, RTT: 32.807596 microseconds
Size: 262144 Bytes, RTT: 60.411665 microseconds
Size: 524288 Bytes, RTT: 116.609156 microseconds
Size: 1048576 Bytes, RTT: 223.720305 microseconds
Size: 2097152 Bytes, RTT: 404.557920 microseconds
Size: 4194304 Bytes, RTT: 735.590770 microseconds

# Dardel 2

Size: 4 Bytes, RTT: 4.462104 microseconds
Size: 8 Bytes, RTT: 4.467377 microseconds
Size: 16 Bytes, RTT: 4.576781 microseconds
Size: 32 Bytes, RTT: 4.510600 microseconds
Size: 64 Bytes, RTT: 4.541498 microseconds
Size: 128 Bytes, RTT: 6.164586 microseconds
Size: 256 Bytes, RTT: 6.065553 microseconds
Size: 512 Bytes, RTT: 5.993708 microseconds
Size: 1024 Bytes, RTT: 5.999625 microseconds
Size: 2048 Bytes, RTT: 6.390054 microseconds
Size: 4096 Bytes, RTT: 6.804722 microseconds
Size: 8192 Bytes, RTT: 7.095415 microseconds
Size: 16384 Bytes, RTT: 7.825340 microseconds
Size: 32768 Bytes, RTT: 13.994433 microseconds
Size: 65536 Bytes, RTT: 17.677218 microseconds
Size: 131072 Bytes, RTT: 24.929927 microseconds
Size: 262144 Bytes, RTT: 38.362802 microseconds
Size: 524288 Bytes, RTT: 62.941115 microseconds
Size: 1048576 Bytes, RTT: 107.986443 microseconds
Size: 2097152 Bytes, RTT: 200.906085 microseconds
Size: 4194304 Bytes, RTT: 385.134623 microseconds

# Dardel 3

Size: 4 Bytes, RTT: 4.125955 microseconds
Size: 8 Bytes, RTT: 4.054353 microseconds
Size: 16 Bytes, RTT: 4.186208 microseconds
Size: 32 Bytes, RTT: 4.142916 microseconds
Size: 64 Bytes, RTT: 4.159377 microseconds
Size: 128 Bytes, RTT: 5.539703 microseconds
Size: 256 Bytes, RTT: 5.786972 microseconds
Size: 512 Bytes, RTT: 6.126462 microseconds
Size: 1024 Bytes, RTT: 5.982364 microseconds
Size: 2048 Bytes, RTT: 6.188180 microseconds
Size: 4096 Bytes, RTT: 6.882890 microseconds
Size: 8192 Bytes, RTT: 7.033723 microseconds
Size: 16384 Bytes, RTT: 7.707226 microseconds
Size: 32768 Bytes, RTT: 14.731663 microseconds
Size: 65536 Bytes, RTT: 19.552133 microseconds
Size: 131072 Bytes, RTT: 27.988556 microseconds
Size: 262144 Bytes, RTT: 42.890272 microseconds
Size: 524288 Bytes, RTT: 67.803664 microseconds
Size: 1048576 Bytes, RTT: 114.785212 microseconds
Size: 2097152 Bytes, RTT: 203.433437 microseconds
Size: 4194304 Bytes, RTT: 395.288102 microseconds

# Dardel 4

Size: 4 Bytes, RTT: 4.350240 microseconds
Size: 8 Bytes, RTT: 4.351698 microseconds
Size: 16 Bytes, RTT: 4.543802 microseconds
Size: 32 Bytes, RTT: 4.330650 microseconds
Size: 64 Bytes, RTT: 4.427386 microseconds
Size: 128 Bytes, RTT: 5.858503 microseconds
Size: 256 Bytes, RTT: 6.120103 microseconds
Size: 512 Bytes, RTT: 6.348043 microseconds
Size: 1024 Bytes, RTT: 6.236500 microseconds
Size: 2048 Bytes, RTT: 6.654863 microseconds
Size: 4096 Bytes, RTT: 7.146283 microseconds
Size: 8192 Bytes, RTT: 7.612167 microseconds
Size: 16384 Bytes, RTT: 8.279132 microseconds
Size: 32768 Bytes, RTT: 15.188932 microseconds
Size: 65536 Bytes, RTT: 19.620961 microseconds
Size: 131072 Bytes, RTT: 28.192439 microseconds
Size: 262144 Bytes, RTT: 43.129590 microseconds
Size: 524288 Bytes, RTT: 68.787442 microseconds
Size: 1048576 Bytes, RTT: 118.085792 microseconds
Size: 2097152 Bytes, RTT: 211.426880 microseconds
Size: 4194304 Bytes, RTT: 384.429873 microseconds

# Dardel 5

Size: 4 Bytes, RTT: 4.182540 microseconds
Size: 8 Bytes, RTT: 4.261823 microseconds
Size: 16 Bytes, RTT: 4.297576 microseconds
Size: 32 Bytes, RTT: 4.274395 microseconds
Size: 64 Bytes, RTT: 4.210612 microseconds
Size: 128 Bytes, RTT: 5.535462 microseconds
Size: 256 Bytes, RTT: 5.668437 microseconds
Size: 512 Bytes, RTT: 5.731280 microseconds
Size: 1024 Bytes, RTT: 5.919322 microseconds
Size: 2048 Bytes, RTT: 6.237907 microseconds
Size: 4096 Bytes, RTT: 6.775653 microseconds
Size: 8192 Bytes, RTT: 7.078280 microseconds
Size: 16384 Bytes, RTT: 7.990784 microseconds
Size: 32768 Bytes, RTT: 13.351446 microseconds
Size: 65536 Bytes, RTT: 16.033843 microseconds
Size: 131072 Bytes, RTT: 21.568959 microseconds
Size: 262144 Bytes, RTT: 33.297986 microseconds
Size: 524288 Bytes, RTT: 55.717607 microseconds
Size: 1048576 Bytes, RTT: 102.141500 microseconds
Size: 2097152 Bytes, RTT: 193.151583 microseconds
Size: 4194304 Bytes, RTT: 373.587528 microseconds

# School Cluster 2

Size: 4 Bytes, RTT: 0.686597 microseconds
Size: 8 Bytes, RTT: 0.677085 microseconds
Size: 16 Bytes, RTT: 0.903640 microseconds
Size: 32 Bytes, RTT: 0.860735 microseconds
Size: 64 Bytes, RTT: 1.068529 microseconds
Size: 128 Bytes, RTT: 0.951634 microseconds
Size: 256 Bytes, RTT: 1.067477 microseconds
Size: 512 Bytes, RTT: 1.381419 microseconds
Size: 1024 Bytes, RTT: 1.664563 microseconds
Size: 2048 Bytes, RTT: 2.138436 microseconds
Size: 4096 Bytes, RTT: 5.195097 microseconds
Size: 8192 Bytes, RTT: 6.956908 microseconds
Size: 16384 Bytes, RTT: 10.691163 microseconds
Size: 32768 Bytes, RTT: 18.192498 microseconds
Size: 65536 Bytes, RTT: 32.130465 microseconds
Size: 131072 Bytes, RTT: 33.474852 microseconds
Size: 262144 Bytes, RTT: 61.631152 microseconds
Size: 524288 Bytes, RTT: 118.396661 microseconds
Size: 1048576 Bytes, RTT: 227.440219 microseconds
Size: 2097152 Bytes, RTT: 408.972390 microseconds
Size: 4194304 Bytes, RTT: 751.801756 microseconds

# School Cluster 3

Size: 4 Bytes, RTT: 0.702341 microseconds
Size: 8 Bytes, RTT: 0.676765 microseconds
Size: 16 Bytes, RTT: 0.863578 microseconds
Size: 32 Bytes, RTT: 0.880897 microseconds
Size: 64 Bytes, RTT: 1.053699 microseconds
Size: 128 Bytes, RTT: 0.952379 microseconds
Size: 256 Bytes, RTT: 1.077896 microseconds
Size: 512 Bytes, RTT: 1.578983 microseconds
Size: 1024 Bytes, RTT: 1.672407 microseconds
Size: 2048 Bytes, RTT: 2.182095 microseconds
Size: 4096 Bytes, RTT: 5.097708 microseconds
Size: 8192 Bytes, RTT: 6.791877 microseconds
Size: 16384 Bytes, RTT: 10.507705 microseconds
Size: 32768 Bytes, RTT: 17.685810 microseconds
Size: 65536 Bytes, RTT: 31.614748 microseconds
Size: 131072 Bytes, RTT: 33.145731 microseconds
Size: 262144 Bytes, RTT: 60.975796 microseconds
Size: 524288 Bytes, RTT: 117.087708 microseconds
Size: 1048576 Bytes, RTT: 225.273199 microseconds
Size: 2097152 Bytes, RTT: 403.737774 microseconds
Size: 4194304 Bytes, RTT: 735.629938 microseconds

# School Cluster 4

Size: 4 Bytes, RTT: 0.700262 microseconds
Size: 8 Bytes, RTT: 0.685666 microseconds
Size: 16 Bytes, RTT: 0.865746 microseconds
Size: 32 Bytes, RTT: 0.884983 microseconds
Size: 64 Bytes, RTT: 1.043444 microseconds
Size: 128 Bytes, RTT: 0.951732 microseconds
Size: 256 Bytes, RTT: 1.076842 microseconds
Size: 512 Bytes, RTT: 1.427374 microseconds
Size: 1024 Bytes, RTT: 1.730564 microseconds
Size: 2048 Bytes, RTT: 2.248179 microseconds
Size: 4096 Bytes, RTT: 5.280550 microseconds
Size: 8192 Bytes, RTT: 6.976118 microseconds
Size: 16384 Bytes, RTT: 10.632947 microseconds
Size: 32768 Bytes, RTT: 17.989167 microseconds
Size: 65536 Bytes, RTT: 31.840599 microseconds
Size: 131072 Bytes, RTT: 33.611545 microseconds
Size: 262144 Bytes, RTT: 61.773375 microseconds
Size: 524288 Bytes, RTT: 118.182224 microseconds
Size: 1048576 Bytes, RTT: 225.811686 microseconds
Size: 2097152 Bytes, RTT: 401.347154 microseconds
Size: 4194304 Bytes, RTT: 732.774957 microseconds

# School Cluster 5

Size: 4 Bytes, RTT: 0.697621 microseconds
Size: 8 Bytes, RTT: 0.674060 microseconds
Size: 16 Bytes, RTT: 0.903321 microseconds
Size: 32 Bytes, RTT: 0.883539 microseconds
Size: 64 Bytes, RTT: 1.063940 microseconds
Size: 128 Bytes, RTT: 0.962315 microseconds
Size: 256 Bytes, RTT: 1.097600 microseconds
Size: 512 Bytes, RTT: 1.429629 microseconds
Size: 1024 Bytes, RTT: 1.473681 microseconds
Size: 2048 Bytes, RTT: 2.019580 microseconds
Size: 4096 Bytes, RTT: 4.916051 microseconds
Size: 8192 Bytes, RTT: 6.717425 microseconds
Size: 16384 Bytes, RTT: 10.247537 microseconds
Size: 32768 Bytes, RTT: 17.072941 microseconds
Size: 65536 Bytes, RTT: 30.393102 microseconds
Size: 131072 Bytes, RTT: 34.297621 microseconds
Size: 262144 Bytes, RTT: 63.489234 microseconds
Size: 524288 Bytes, RTT: 122.332717 microseconds
Size: 1048576 Bytes, RTT: 237.362311 microseconds
Size: 2097152 Bytes, RTT: 413.450801 microseconds
Size: 4194304 Bytes, RTT: 740.836494 microseconds