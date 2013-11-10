-- --------------------------------------------------------------- --
--                                                                 --
--                                                                 --
--          Universidade Federal de Minas Gerais - UFMG            --
--              Departamento de Ciência da Computação              --
--          -------------------------------------------            --
--          Júlio Albinati, Paulo Bicalho, Rubens Emilio           --
--            {jalbinati,p.bicalho,rubens}@dcc.ufmg.br             --
--                                                                 --
--                                                                 --
-- --------------------------------------------------------------- --

-- If we shall fail, we will fail. But screw thy courage
-- to the sticking place, and we shall not fail!

   This is a free and open source multiplayer game, written in C++
and Allegro 5. This application is part of a Software Engineering
assignment. The code is also publicly available at [1]. If any
questions, suggestions, or even donations, don't forget to mail us (:

-- --------------------------------------------------------------- --
-- Compilation:

   To compile the code you must have Allegro[1] library (5.0.10)
installed, and cmake[2] utilitary (>= 2.8) must also be available.
Finally, you must have g++ (>= 4.?) to be able to compile the code.

Once all dependecies are solved, run the following command from
within the directory 'bin/':

   cmake ../src/
   make

   This shall build the application in the current folder,
and compile the code.

-- --------------------------------------------------------------- --
-- Execution:
   
   Once compiled, to run the application, simply run the following
command line, from within the directory 'bin/':

   ./gIrAfA

-- --------------------------------------------------------------- --
-- Links:

[1] - https://github.com/Speederama/EngSoft
[2] - http://alleg.sourceforge.net/download.html
[3] - http://www.cmake.org/cmake/resources/software.html
