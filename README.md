# DepthPerceptionSimulator
reference https://inst.eecs.berkeley.edu/~cs61c/fa14/projs/01/
Usage:
$ make
$ ./depth_map
<p>
USAGE: ./depth_map [options] <br>

REQUIRED <br>
    -l [LEFT_IMAGE]       The left image <br>
    -r [RIGHT_IMAGE]      The right image <br>
    -w [WIDTH_PIXELS]     The width of the smallest feature <br>
    -h [HEIGHT_PIXELS]    The height of the smallest feature <br>
    -t [MAX_DISPLACE]     The threshold for maximum displacement <br>

OPTIONAL
    -o [OUTPUT_IMAGE]     Draw output to this file <br>
    -v                    Print the output to stdout as readable bytes <br>
</p>

Example: <br>
$ ./depth_map -l test/images/quilt2-left.bmp -r test/images/quilt2-right.bmp -h 0 -w 0 -t 1 -o test/output/quilt2-output.bmp -v
