```shell
(base) computer@computers-MacBook-Air prog1_mandelbrot_threads % ./mandelbrot 
[mandelbrot serial]:            [418.188] ms
Wrote image file mandelbrot-serial.ppm
Hello world from thread 0
Hello world from thread 1
Hello world from thread 0
Hello world from thread 1
Hello world from thread 0
Hello world from thread 1
Hello world from thread 0
Hello world from thread 1
Hello world from thread 0
Hello world from thread 1
[mandelbrot thread]:            [216.760] ms
Wrote image file mandelbrot-thread.ppm
                                (1.93x speedup from 2 threads)
```

```angular2html
(base) computer@computers-MacBook-Air prog1_mandelbrot_threads % ./mandelbrot -t 10
[mandelbrot serial]:            [419.273] ms
Wrote image file mandelbrot-serial.ppm
Hello world from thread 0
Hello world from thread 1
Hello world from thread 9
Hello world from thread 8
Hello world from thread 7
Hello world from thread 2
Hello world from thread 3
Hello world from thread 6
Hello world from thread 5
Hello world from thread 4
Hello world from thread 0
Hello world from thread 1
Hello world from thread 9
Hello world from thread 8
Hello world from thread 2
Hello world from thread 7
Hello world from thread 6
Hello world from thread 3
Hello world from thread 5
Hello world from thread 4
Hello world from thread 0
Hello world from thread 9
Hello world from thread 1
Hello world from thread 8
Hello world from thread 2
Hello world from thread 7
Hello world from thread 6
Hello world from thread 3
Hello world from thread 4
Hello world from thread 5
Hello world from thread 0
Hello world from thread 9
Hello world from thread 1
Hello world from thread 8
Hello world from thread 2
Hello world from thread 7
Hello world from thread 6
Hello world from thread 3
Hello world from thread 4
Hello world from thread 5
Hello world from thread 0
Hello world from thread 9
Hello world from thread 1
Hello world from thread 8
Hello world from thread 2
Hello world from thread 7
Hello world from thread 3
Hello world from thread 6
Hello world from thread 5
Hello world from thread 4
[mandelbrot thread]:            [109.532] ms
Wrote image file mandelbrot-thread.ppm
                                (3.83x speedup from 10 threads)

```

```angular2html
(base) computer@computers-MacBook-Air prog1_mandelbrot_threads % ./mandelbrot -t 20
[mandelbrot serial]:            [417.786] ms
Wrote image file mandelbrot-serial.ppm
Hello world from thread 1
Hello world from thread 2
Hello world from thread 3
Hello world from thread 19
Hello world from thread 0
Hello world from thread 18
Hello world from thread 17
Hello world from thread 5
Hello world from thread 16
Hello world from thread 4
Hello world from thread 9
Hello world from thread 15
Hello world from thread 13
Hello world from thread 8
Hello world from thread 6
Hello world from thread 14
Hello world from thread 7
Hello world from thread 11
Hello world from thread 12
Hello world from thread 10
Hello world from thread 0
Hello world from thread 1
Hello world from thread 2
Hello world from thread 3
Hello world from thread 18
Hello world from thread 17
Hello world from thread 19
Hello world from thread 16
Hello world from thread 15
Hello world from thread 4
Hello world from thread 6
Hello world from thread 13
Hello world from thread 5
Hello world from thread 14
Hello world from thread 7
Hello world from thread 12
Hello world from thread 11
Hello world from thread 8
Hello world from thread 9
Hello world from thread 10
Hello world from thread 0
Hello world from thread 1
Hello world from thread 19
Hello world from thread 18
Hello world from thread 3
Hello world from thread 17
Hello world from thread 2
Hello world from thread 4
Hello world from thread 16
Hello world from thread 15
Hello world from thread 13
Hello world from thread 5
Hello world from thread 14
Hello world from thread 6
Hello world from thread 9
Hello world from thread 12
Hello world from thread 7
Hello world from thread 11
Hello world from thread 8
Hello world from thread 10
Hello world from thread 0
Hello world from thread 1
Hello world from thread 2
Hello world from thread 18
Hello world from thread 19
Hello world from thread 17
Hello world from thread 3
Hello world from thread 16
Hello world from thread 15
Hello world from thread 14
Hello world from thread 4
Hello world from thread 13
Hello world from thread 5
Hello world from thread 6
Hello world from thread 7
Hello world from thread 12
Hello world from thread 11
Hello world from thread 8
Hello world from thread 9
Hello world from thread 10
Hello world from thread 0
Hello world from thread 1
Hello world from thread 2
Hello world from thread 19
Hello world from thread 3
Hello world from thread 18
Hello world from thread 16
Hello world from thread 17
Hello world from thread 5
Hello world from thread 4
Hello world from thread 15
Hello world from thread 14
Hello world from thread 13
Hello world from thread 6
Hello world from thread 8
Hello world from thread 7
Hello world from thread 12
Hello world from thread 10
Hello world from thread 11
Hello world from thread 9
[mandelbrot thread]:            [80.900] ms
Wrote image file mandelbrot-thread.ppm
                                (5.16x speedup from 20 threads)
(base) computer@computers-MacBook-Air prog1_mandelbrot_threads % ./mandelbrot -t 8 
[mandelbrot serial]:            [418.020] ms
Wrote image file mandelbrot-serial.ppm
Hello world from thread 0
Hello world from thread 7
Hello world from thread 1
Hello world from thread 6
Hello world from thread 5
Hello world from thread 2
Hello world from thread 3
Hello world from thread 4
Hello world from thread 0
Hello world from thread 7
Hello world from thread 1
Hello world from thread 6
Hello world from thread 2
Hello world from thread 5
Hello world from thread 3
Hello world from thread 4
Hello world from thread 0
Hello world from thread 7
Hello world from thread 1
Hello world from thread 6
Hello world from thread 2
Hello world from thread 5
Hello world from thread 4
Hello world from thread 3
Hello world from thread 0
Hello world from thread 7
Hello world from thread 6
Hello world from thread 1
Hello world from thread 5
Hello world from thread 2
Hello world from thread 3
Hello world from thread 4
Hello world from thread 0
Hello world from thread 7
Hello world from thread 6
Hello world from thread 1
Hello world from thread 2
Hello world from thread 5
Hello world from thread 4
Hello world from thread 3
[mandelbrot thread]:            [121.917] ms
Wrote image file mandelbrot-thread.ppm
                                (3.43x speedup from 8 threads)
(base) computer@computers-MacBook-Air prog1_mandelbrot_threads % 

```