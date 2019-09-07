<h1 align="center">42 FDF</h1>
<br>

*This project is about creating a simplified 3D graphic representation of a relief landscape. (in C)*

> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;In this project you will discover the basics of graphic programming, and in particular how
to place points in space, how to join them with segments and most importantly how to
observe the scene from a particular viewpoint.

> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;You will also discover your first graphic library: miniLibX. This library was developed
internally and includes the minimum necessary to open a window, light a pixel and deal
with events linked to this window: keyboard and mouse. This project introduces you to
“events” programming. -pedago@42.fr

Many thanks to:
* [Mohammad](https://github.com/mohammadbutt) for helping me out with testing.
* [Jimmy](https://github.com/Zeroays) for helping me make the python script.
* [Jeff Senpai](https://github.com/JCTGY) for feedbacks.
* [Vladyslav Brazhnik](https://github.com/VBrazhnik) for his FDF cook book.
* [Tigran Katolikyan](https://github.com/katolikyan) for the depth effect.
* [Mr Colour](https://github.com/mrcolour) for coding advices.
* [Jean-Michel Gigault](https://github.com/jgigault) for his map generator.
* And of course [42 Silicon Valley](https://www.42.us.org) for giving me this opportunity to work on this project.
<p float ="left">
  <img src="images/fdf_miku_dance.gif" width="350" alt="original gif" title="Miku dance" hspace="50"/>
  <img src="images/miku_dance_demo.gif" width="350" alt="fdf miku" title="Miku dance in fdf"/>
  <br><br>
</p>

## Table of Content
- [Project Overview](#project-overview)
  * [fdf files](#fdf-files)
  * [Line Algorithm](#line-algorithm)
   + [Color Issue](#color-issue)
   + [Brightness Issue](#brightness-issue)
- [Compatibility](#compatibility)
- [How to run](#how-to-run)
  * [FDF minishell](#fdf-minishell)
- [Gradient](#gradient)
- [Preview](#preview)
- [Gif](#gif)
- [Update Log](#update-log)

### Project Overview
Given a .fdf file with this format
```txt
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```
Each number represents a point with a height in integer.\
The goal is to draw a line connecting each point and represent them all together as a landscape.

### fdf files
There is no set limit of how big the fdf files should be. However, a valid file should have same amount of points on each line. Each line is ended with a newline. There are no extra empty lines between lines, at the end or at the beginning of the file. Value of the points must be within integer limit.\
To further represent a landscape, an integer represent in hex for color can be added behind the points separated by a comma.
```txt
0,0xffffff 0,ffffff
0,0xFFFFFF 0,FFFFFF
# All are valid representation of color white

0,0xff 0,0x0000ff
0,0xFF 0,0x0000FF
# Works with 0 paddings as well.
```
In order to read the files, students are only allowed to use **open()** and **read()**.\
The 2nd project get_next_line() at 42 is the main key for me to parse the file and grab each line. It works similar to **getline()** function.
```C
prototype:

int	get_next_line(const int fd, char **line);
returns
-1 if there's an error     0 if end of file     1 if successful
```
After grabbing the line, I use **ft_strsplit()**, a function that I made in my first create-your-own-library project at 42, to split all the digits up using a space (' ') as a delimiter or 32 in ascii. After splitting them up, I use **ft_atoi()** similar to **atoi()** to convert them into integers. I also use ft_strsplit() with (',') as delimiter to extract the color behind the points. To convert the hex to integer, I make a simple **ft_atoi_base()** that allows me to convert the hex string into integer using base 16. I store the points in t_map struct.
```C
typedef struct		s_map
{
	int		*map; // store points
	int		*c_map; // store color
	int		map_h; // height (how many lines in the file)
	int		map_w; // width (how many points in a line)
	int		map_size; // width x height
	bool		map_color; // true if color mapping exist, false then use default color.
}					t_map;
```
#### Line Algorithm
After seeing so many students at the school use the [Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) for their project, I decided to try to [Xiaolin Wu's algorithm](https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm) instead.
Since I cannot have more than 5 variables declared in a function, school rule, I have to use a struct to store them.
```C
typedef struct		s_var
{
	bool	steep;
	bool	swap; // color swap
	bool	swap_d; // color swap
	double	dx;
	double	dy;
	double	gradient;
	double	xend;
	double	yend;
	double	xgap;
	double	ygap;
	int	xpxl1;
	int	ypxl1;
	double	intery;
	double	interx;
	int	xpxl2;
	int	ypxl2;
}					t_var;
```
The wikipedia does not declare variables type, so in the beginning all my variables are doubles. But after referencing the
[rosettacode](https://rosettacode.org/wiki/Xiaolin_Wu%27s_line_algorithm#C), I decide to change some doubles to int.\
It is not hard to implement the wikipedia algorithm. However I run into issues with color and lightning (brightness).\
##### Color Issue
```C
if (var->steep)
{
	var->swap = true;
	ft_swap(&(p0->x), &(p0->y));
	ft_swap(&(p1->x), &(p1->y));
}
if (p0->x > p1->x)
{
	if (!var->steep)
		var->swap = true;
	var->swap_d = true;
	ft_swap(&(p0->x), &(p1->x));
	ft_swap(&(p0->y), &(p1->y));
}
```
The points are being swapped around in the algorithm. Each of the points has a certain rgb value and having them swapped around causes all sort of problems for me when I implement color gradient. That is the main reason why I have to add boolean variables to keep track of what's being swapped so the program will draw correct color.\

##### Brightness Issue
```txt
# Debug mode
...
bright: 0.658824	 percent: 0.811765	rgb_start(87,63,38)	rgb_end(84,60,35)	rgb_ret(55, 39, 23)
bright: 0.882353	 percent: 0.823529	rgb_start(87,63,38)	rgb_end(84,60,35)	rgb_ret(74, 53, 31)
bright: 0.117647	 percent: 0.823529	rgb_start(87,63,38)	rgb_end(84,60,35)	rgb_ret(9, 7, 4)
bright: 0.423529	 percent: 0.835294	rgb_start(87,63,38)	rgb_end(84,60,35)	rgb_ret(35, 25, 15)
bright: 0.576471	 percent: 0.835294	rgb_start(87,63,38)	rgb_end(84,60,35)	rgb_ret(48, 34, 20)
bright: 0.964706	 percent: 0.847059	rgb_start(87,63,38)	rgb_end(84,60,35)	rgb_ret(81, 58, 34)
bright: 0.035294	 percent: 0.847059	rgb_start(87,63,38)	rgb_end(84,60,35)	rgb_ret(2, 2, 1)
...
ret.r = ((start.r * (1.0 - percent)) + (end.r * percent)) * brightness;
```
Looking at the value, you can see that the brightness never reaches 1.0 (maximum brightness). That means, the pixel I got out of the algorithm never reaches their true color. The colors return are much dimmer. To counter it, I just add 0.2 brightness to make them 20% brighter. To fully make it brightest possible, I modify my main loop like so.
```C
// before
plot_pixel(fdf, var.xpxl1, ipart(var.intery), get_color(p0, p1, percent, rfpart(var.intery))); //anti-aliasing
// after
plot_pixel(fdf, var.xpxl1, ipart(var.intery), get_color(p0, p1, percent, 1.0)); // not anti-aliasing
```
By increasing the brightness to 1.0 for every pixel, the lines are no longer anti-aliasing. So, basically, I have "2" line algorithm inside the program. After the switch, I can see that the lines are twice as thick in parallel view. I make the anti-alias button for users to see the difference.
### Compatibility
*(only tested on this machine)*\
**about this mac**\
iMac (Retina 5K, 27-inch, Late 2015)\
3.2 GHz Intel Core i5\
AMD Radeon R9 M380 2048 MB

**gcc --version**\
Apple LLVM version 9.1.0 (clang-902.0.39.1)\
Target: x86_64-apple-darwin17.5.0\
Thread model: posix

**make --version**\
GNU Make 3.81

### How to run
```
make
./fdf [path to .fdf files]
```
#### fdf minishell
Pressing S will enter shell mode, program will not resume until "resume" command is input
<p align="center">
  <img src="images/fdf_minishell.png" height="500" title="fdf_minishell">
</p>

### Gradient
![](images/default_gradient_test.png)
<img src="images/theme.png" title="generated by gradient test function in test.c">
You can customize your own theme (custom default is black to white)
```c
void fdf_theme_custom(t_ramp **ramp)
{
  color_ramp(ramp, FDF_A, steps, FDF_B); //starting color ramp for FDF_A is for lowest z
  ...
  color_ramp(ramp, FDF_Y, steps, FDF_Z); //ending color ramp for FDF_Z is for highest z
}
```

### Preview

<p align="center">
  <b>Gulf of California Ocean</b><br><br>
  <b>Parallel view:</b><br><br>
  <table border="0" cellpadding="5">
  <tr>
    <td align="center" valign="center">
      <img src="images/map_parallel_normal.png" width="250" title="parallel without AA" hspace="80"/>
      <br>
      Without anti-aliasing
    </td>
    <td align="center" valign="center">
      <img src="images/map_parallel_anti_alias.png" width="250" title="parallel with AA" hspace="80"/>
      <br>
      With anti-aliasing
    </td>
   </tr>
   </table>
</p>
<p align="center">
  <b>Isometric view:</b><br><br>
  <img src="images/map_iso_normal.png" height="350" title="iso without AA" />
  <img src="images/map_iso_anti_alias.png" height="350" title="iso with AA" />
</p>

### GIF

#### How to make your own fdf gifs
1. Convert a gif to bmp (make sure to give it an easy name before converting)\
I use this [site](https://image.online-convert.com/convert-to-bmp)\
Normally I prefer width around 250 to 300, depending on your program. Just compile with -02 or -03 to make them run faster.
2. Put all the bmp files into a folder and place the bmp folder into the fdf folder
3. Create a new folder to store fdf files
4. Run the the [python script](https://github.com/nkone/42_fdf/blob/master/maps/script/pixel.py) like so (located in maps/script)
```shell
for f in [BMP FOLDER PATH]/*.bmp; do
python3 pixel.py $f [OUTPUT FOLDER PATH]; done
```
5. Rename the files\
When converting gif to bmp, you'd often see something like [prefix]-{0...x}.bmp. To read them in lexicographically order run
```shell
# replace PREFIX with name of your file without numbers at the end
printf '%s\n' *(n) | cat -n | while read n f; do mv $f `printf "[PREFIX]%04d.fdf" $n`; done
# Your files now have 0 paddings.
```
6. Start fdf and run any fdf files
7. Enter shell mode and use animate

You can get results like these:
<details>
   <summary>Game</summary>
   <br>
   <p align ="center">
     <b>Fighting Climax Ignition: Shana</b><br><br>
     <img src="images/shana_combo.gif" width="400" /><br>
     <img src="images/shana_combo_demo.gif" title="shana demo 250 x 141"width="1000" />
   </p>
</details>
<details>
  <summary>Matrix</summary>
  <p align ="center">
  <b>Matrix bullet dodging</b><br><br>
  <img src="images/matrix_bullet.gif" width="400" /><br>
  <img src="images/matrix_bullet_demo.gif" title ="matrix demo with AA off @ 250 x 103"width="1000" />
  </p>
</details>
<details>
  <summary>Isopoly</summary>
  <p align ="center">
  <b>Isopoly for "3D"</b><br><br>
  <img src="images/isopoly.gif" width="400" /><br>
  <img src="images/isopoly_demo.gif" title ="isopoly demo @ 128 x 128" width="1000" />
  </p>
</details>
If you find program runs too fast, you can increase the resolution of the bmp(make new ones) or add in a delay function.
<details><summary>spoiler</summary><br>
	
```c
// Something like this
void	delay(int milliseconds)
{
	unsigned long	pause;
	clock_t			now;
	clock_t			then;

	pause = milliseconds * (CLOCKS_PER_SEC / 1000);
	then = clock();
	now = then;
	while ((now - then) < pause)
		now = clock();
}
```
</details>

#### Update Log
<details><summary>September</summary><br>
<b>09/07/2019</b><br><br>
	
 + Extra
   + Added project overview
   
<b>09/06/2019</b><br>

 + Code
   + Fixed minor math issue and increase brightness by 20% for anti alias
 + Image assets
   + Added better resolution pictures for comparison between AA and normal
   + Added pictures for minishell
 + Extra
   + Update shell_help.txt
   + Added explanation for gifs
   + Added explanation for how to run
 
<b>09/05/2019</b><br>

 + Code
   + Change algorithm to use int instead of doubles.
   + Added rosetta code algo for comparison.
   + Added functionality for alias.
 + Image assets
   + Fix resolution after adding anti alias
   + Update better gifs for matrix
   + Gifs are now collapsible
    
</details>
