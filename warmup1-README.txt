
Anjali Gopal Reddy 
anjaligr@usc.edu

Documentation for Warmup Assignment 1
=====================================
 +---------------------+
 | Warmup1 README file |
 +---------------------+

+-------+
| BUILD |
+-------+

Please type make to create an executable warmup1 required to run the program.        

+------+
| SKIP |
+------+

None

+---------+
| GRADING |
+---------+

This section contains self assessment of the grading guidelines.

The output from my program against grading guidelines is displayed as "OUTPUT: ..."

+--------------+
| Plus points: |
+--------------+

(A) Doubly-linked Circular List : +40 points
                set srcdir=~csci570b/public/cs402/warmup1
				
				/bin/rm -rf grading_$$
                        mkdir grading_$$
                        cd grading_$$
                        cp ../my402list.c .
                        cp $srcdir/cs402.h .
                        cp $srcdir/my402list.h .
                        cp $srcdir/listtest.c .
                        cp $srcdir/Makefile .
                        make

				foreach f (0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19)
                            echo "===> test_$f"
                            ./listtest
                        end
OUTPUT:	

===> test_0
===> test_1
===> test_2
===> test_3
===> test_4
===> test_5
===> test_6
===> test_7
===> test_8
===> test_9
===> test_10
===> test_11
===> test_12
===> test_13
===> test_14
===> test_15
===> test_16
===> test_17
===> test_18
===> test_19


Marks:  +40


---------------------------------------------------------------------------------------------------------
(B) Sort : +60 points
			set srcdir=~csci570b/public/cs402/warmup1
			
			#
                # (B1)
                # for the following commands, each case is worth 2 points
                # gets 2 points if "diff" command produces NOTHING
                # gets 1 point if "diff" command produces SOME output showing
                #     only formatting errors (i.e., all information are correct)
                # gets 0 point if "diff" command produce SOME output showing
                #     incorrect information in the output
                #
				
				/bin/rm -f f?.sort f??.sort
                foreach f (0 1 2 3 4 5 6 7 8 9 10 11 12 13 14)
                    echo "===> $srcdir/f$f"
                    ./warmup1 sort $srcdir/f$f > f$f.sort
                    diff $srcdir/f$f.sort f$f.sort
                end
                /bin/rm -f f?.sort f??.sort
                
    OUTPUT:
    
===> /home/scf-08/csci570b/public/cs402/warmup1/f0
===> /home/scf-08/csci570b/public/cs402/warmup1/f1
===> /home/scf-08/csci570b/public/cs402/warmup1/f2
===> /home/scf-08/csci570b/public/cs402/warmup1/f3
===> /home/scf-08/csci570b/public/cs402/warmup1/f4
===> /home/scf-08/csci570b/public/cs402/warmup1/f5
===> /home/scf-08/csci570b/public/cs402/warmup1/f6
===> /home/scf-08/csci570b/public/cs402/warmup1/f7
===> /home/scf-08/csci570b/public/cs402/warmup1/f8
===> /home/scf-08/csci570b/public/cs402/warmup1/f9
===> /home/scf-08/csci570b/public/cs402/warmup1/f10
===> /home/scf-08/csci570b/public/cs402/warmup1/f11
===> /home/scf-08/csci570b/public/cs402/warmup1/f12
===> /home/scf-08/csci570b/public/cs402/warmup1/f13
===> /home/scf-08/csci570b/public/cs402/warmup1/f14


			 #
                # (B2)
                # for the following commands, each case is worth 2 points
                # gets 2 points if "diff" command produces NOTHING
                # gets 1 point if "diff" command produces SOME output showing
                #     only formatting errors (i.e., all information are correct)
                # gets 0 point if "diff" command produce SOME output showing
                #     incorrect information in the output
                #
                /bin/rm -f f??.sort
                foreach f (15 16 17 18 19 20 21 22 23 24 25 26 27 28 29)
                    echo "===> $srcdir/f$f"
                    cat $srcdir/f$f | ./warmup1 sort > f$f.sort
                    diff $srcdir/f$f.sort f$f.sort
                end
                /bin/rm -f f??.sort

OUTPUT:
===> /home/scf-08/csci570b/public/cs402/warmup1/f15
===> /home/scf-08/csci570b/public/cs402/warmup1/f16
===> /home/scf-08/csci570b/public/cs402/warmup1/f17
===> /home/scf-08/csci570b/public/cs402/warmup1/f18
===> /home/scf-08/csci570b/public/cs402/warmup1/f19
===> /home/scf-08/csci570b/public/cs402/warmup1/f20
===> /home/scf-08/csci570b/public/cs402/warmup1/f21
===> /home/scf-08/csci570b/public/cs402/warmup1/f22
===> /home/scf-08/csci570b/public/cs402/warmup1/f23
===> /home/scf-08/csci570b/public/cs402/warmup1/f24
===> /home/scf-08/csci570b/public/cs402/warmup1/f25
===> /home/scf-08/csci570b/public/cs402/warmup1/f26
===> /home/scf-08/csci570b/public/cs402/warmup1/f27
===> /home/scf-08/csci570b/public/cs402/warmup1/f28
===> /home/scf-08/csci570b/public/cs402/warmup1/f29
    
Marks: +60

------------------------------------------------------------------------------------------------------

+---------------+
| Minus points: |
+---------------+

Missing required section(s) in README file : No

Cannot compile : -0 ( The program compiles.)

Compiler warnings : -0 (No compiler warnings.)

"make clean" : -0 (Deletes all binary files. )

Segmentation faults : -0 (No segmentation faults.)

Separate compilation :  -0 (follows separate compilation)

Malformed input : -0 (See output against grading guideline below.)

Too slow : -0 (Not slow )

Bad commandline : -0 (See output against grading guideline below.)

Bad behavior for random input : -0 (No bad behaviour noticed.)

Did not use My402List and My402ListElem to implement "sort" in (B) : -0 (Used My402List and My402ListElem to implement "sort" in (B))


Malformed input :

				set srcdir=~csci570b/public/cs402/warmup1

				cat $srcdir/f101 | ./warmup1 sort
OUTPUT:			Invalid Input. Time cannot be greater than current time
                
                cat $srcdir/f102 | ./warmup1 sort
OUTPUT:         Invalid Input in transaction sign       
                
                cat $srcdir/f103 | ./warmup1 sort
OUTPUT:         Invalid Input in numbers after decimal point (Only 2)
                
                cat $srcdir/f104 | ./warmup1 sort
OUTPUT:         Invalid Input in Description
                
                cat $srcdir/f105 | ./warmup1 sort
OUTPUT:         Invalid Input. Three tab delimited fields required
				Exited
                
                cat $srcdir/f106 | ./warmup1 sort
OUTPUT:         Invalid Input in string length. Only 1024 characters are allowed.
                
                cat $srcdir/f107 | ./warmup1 sort
OUTPUT:		Invalid Input. Same time stamp exists!.	

Bad commandline or command :

				set srcdir=~csci570b/public/cs402/warmup1
				
				./warmup1
OUTPUT:       	usage: warmup1 sort [tfile]

                ./warmup1 -y sort
OUTPUT:       	usage: warmup1 sort [tfile]

                ./warmup1 xyz
OUTPUT:       	usage: warmup1 sort [tfile]

                ./warmup1 abc def ghi
OUTPUT:       	usage: warmup1 sort [tfile]
 
                ./warmup1 ksjdfjwiejofjasdfjowkejokjaosijfioejfsiejriwjeirjwier
OUTPUT:       	usage: warmup1 sort [tfile]

                ./warmup1 sort -x
OUTPUT:			Cannot open -x for reading.
				Error: No such file or directory
				
                ./warmup1 sort /usr/bin/xyzz
OUTPUT:			Cannot open /usr/bin/xyzz for reading.
				Error: No such file or directory

                ./warmup1 sort /etc/sysidcfg
OUTPUT:         Cannot open /etc/sysidcfg for reading.
				Error: Permission denied

				./warmup1 sort /etc/inet/secret/xyzz
OUTPUT:         Cannot open /etc/inet/secret/xyzz for reading.
				Error: Permission denied
 
                ./warmup1 sort /etc
OUTPUT:         Cannot open /etc for reading. It is a directory.
                    
                ./warmup1 sort /etc/motd
OUTPUT:         Invalid Input. Three tab delimited fields required
				Exited
                    
                ./warmup1 sort ~/.login
OUTPUT:         Invalid Input. Three tab delimited fields required
				Exited
				
				
+------+
| BUGS |
+------+

None

+-------+
| OTHER |
+-------+

No deviation from spec.

		
+-------+
|  END  |
+-------+
				
				
				
				
				
				


  
  


