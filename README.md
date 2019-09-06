# 42_fdf
Many thanks to:
* [Mohammad](https://github.com/mohammadbutt) for helping me out with testing.
* [Vasu aka Jimmy](https://github.com/Zeroays) for helping me make the python script.
* [Vladyslav Brazhnik](https://github.com/VBrazhnik) for his FDF cook book.
* [Tigran Katolikyan](https://github.com/katolikyan) for the depth effect.
* [Mr Colour](https://github.com/mrcolour) for coding advices.
* And of course 42 Silicon Valley for giving me this opportunity to work on this project.
<p float ="left">
  <img src="images/fdf_miku_dance.gif" width="350" alt="original gif" title="Miku dance" hspace="50"/>
  <img src="images/miku_dance_demo.gif" width="350" alt="fdf miku" title="Miku dance in fdf"/>
  <br><br>
</p>

## Compatibility (only tested with school machine):

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

Wireframe graphic

How to run
```
make
./fdf [path to .fdf files]
```

### Gradient
![](images/default_gradient_test.png)
Theme demo:
![](images/theme.png)

<p align="center">
  <b>Gulf of California Ocean</b><br><br>
  <b>Parallel view:</b><br><br>
  <img src="images/map_parallel_normal.png" width="250" title="gulf of california ocean parallel"/>
  <img src="images/map_parallel_anti_alias.png" width="250" title="gulf of california ocean parallel with anti_alias"/>
  <br><br>
  <b>Isometric view:</b><br><br>
  <img src="images/map_iso_normal.png" width="500" title="gulf of califronia ocean iso"/>
</p>

### GIF demonstration

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
  <img src="images/matrix_bullet_demo.gif" title ="matrix demo with anti-alias off @ 250 x 103"width="1000" />
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
                                                 
#### Update Log
<details>
  <summary>September</summary>
  <details>
    <summary>September 6</summary>
    <br>
  
      + Code
        + Fixed minor math issue and increase brightness by 20% for anti alias
    
   </details>
   <details>
      <summary>September 5</summary>
      <br>
  
      + Code
        + Change algorithm to use int instead of doubles.
        + Added rosetta code algo for comparison.
        + Added functionality for alias.
      + Gifs
        + Fix resolution after adding anti alias
        + Update better gifs for matrix
        + Gifs are now collapsible
  
   </details>
</details>

  
