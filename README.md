# Recurrent-Square-Filling-Curves
Recurrent functions which use the Hilbert, Peano and Z curves to fill squares of many $2^m \times 2^m$ dimensionalities. Those funtions do mainly output a 2D map of the output curve. It is meant to be a more efficient symmetric mapping of 2D images into 1D lin spaces. *1

## Content
In this repo is one recursive funtion:

### Recursive Hilbert-Peano Function
 
it can break down from any dxd square which is able to be break down in 2x2 and 3x3 bases.<br>
Thus everything which does not break down to 5 or 7 using 2x2 and 3x3 patterns!<br>
it has an asymetric $3 \times 3$ base in case of a hulbert structure before.

## Map Examples

### 12x12 Map


#### Peano-hilbert
```bash
$ bin/print_2d_curves
Welcome to the 2D space filling curves!
This is a demo outputting a 2D map of the indices.
But caution, those functions currently only support 2^n and 3^n elements sqare areas!
And keep in mind that large matrices couldn't be displayed here!
Please input you desired side length: 12
Do you want to run the verb ose mode?
(y/n)
n
Hilbert-Peano map:
  47   48   49   58   59   60   83   84   85   94   95   96
  46   51   50   57   56   61   82   87   86   93   92   97
  45   52   53   54   55   62   81   88   89   90   91   98
  44   43   42   65   64   63   80   79   78  101  100   99
  37   38   41   66   69   70   73   74   77  102  105  106
  36   39   40   67   68   71   72   75   76  103  104  107
  35   34   27   26   25   24  119  118  117  116  109  108
  32   33   28   19   20   23  120  123  124  115  110  111
  31   30   29   18   21   22  121  122  125  114  113  112
   4    5    6   17   14   13  130  129  126  137  138  139
   3    2    7   16   15   12  131  128  127  136  141  140
   0    1    8    9   10   11  132  133  134  135  142  143
```

![alt text](https://github.com/markusMM/Recurrent-Square-Filling-Curves/raw/master/plot/12x12_HilbertPeano.png "12x12 Hilbert-Peano")

## Compilation

You need flags `-lgsl`, `-lgslcblas` and `-lm` (`-lm` can be ignored in Windows MinGW x64/x84 compiler).
Example for the matrix print:
```bash
$ gcc src/print_2d_curves.c src/helpers_2d.c src/hilbert_peano.c -o bin/print_2d_curves -lgsl -lgslcblas -lm
```

## Notes
*1: WARNING: This type of mappings is rare for deep learning image recognition tasks and does probably not work on pretrained networks, since they are most of the time either convolutional and/or in some kind of sense trained on a simple stack reshape of the input images.
