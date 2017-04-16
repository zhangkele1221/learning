    操作系统(Operating System, OS)
是指控制和管理整个计算机系统的硬件和软件资源，
并合理地组织调度计算机的工作和资源的分配，
以提供给用户和其他软件方便的接口和环境的程序集合。
计算机操作系统是随着计算机研究和应用的发展逐步形成并发展起来的，
它是计算机系统中最基本的系统软件。




操作系统是一种系统软件，但与其他的系统软件和应用软件有很大的不同，
它有自己的特殊性即基本特征。
操作系统的基本特征包括--（并发、 共享、 虚拟 和 异步）。

*******************************************************************
      并发(Concurrence)

并发是指两个或多个事件在同一时间 间隔内发生。
操作系统的并发性是指计算机系统中同时存在多个运行着的程序，
因此它具有处理和调度多个程序同时执行的能力。
在操作系统中，引入进程的目的是使程序能并发执行。
***********注意同一时间间隔（并发）和同一时刻（并行）的区别。******
在多道程序环境下，一段时间内，宏观上有多道程序在同时执行，
而在每一时刻，单处理机环境下实际仅能有一道程序执行，
故微观上这些程序还是在分时地交替执行。
橾作系统的并发性是通过分时得以实现的。
----------------------------------------------------------------
注意，并行性是指系统具有可以同时进行运算或操作的特性，
在同一时刻完成两种或两种以上的工作。
并行性需要有相关硬件的支持，如多流水线或多处理机硬件环境。
**********************************************************************

！！！！！！！！！！！！！！！结论！！！！！！！！！！！！！！！
1 你吃饭吃到一半，电话来了，你一直到吃完了以后才去接，
这就说明你不支持并发也不支持并行。

2 你吃饭吃到一半，电话来了，你停了下来接了电话，接完后继续吃饭，
这说明你支持并发。

3 你吃饭吃到一半，电话来了，你一边打电话一边吃饭，
这说明你支持并行。

4 并发的关键是你有处理多个任务的能力，不一定要同时。
  
5 并行的关键是你有同时处理多个任务的能力。
所以我认为它们最关键的点就是：是否是『同时』。


    共享（Sharing)
资源共享即共享，是指系统中的资源可供内存中多个并发执行的进程共同使用。
共享可分为以下两种资源共享方式：
1) 互斥共享方式
系统中的某些资源，如打印机、磁带机，虽然它们可以提供给多个进程使用，
但为使所打印或记录的结果不致造成混淆，
应规定在一段时间内只允许一个进程访问该资源。
---为此，当进程A访问某资源时，必须先提出请求，
如果此时该资源空闲，系统便可将之分配给进程A使用，
此后若再有其他进程也要访问该资源时（只要A未用完）则必须等待。
仅当进程A访问完并释放该资源后，才允许另一进程对该资源进行访问。
我们把这种资源共享方式称为互斥式共享，
--而把在一段时间内只允许一个进程访问的资源称为(临界资源)或(独占资源)。
计算机系统中的大多数物理设备，以及某些软件中所用的栈、变量和表格，
都属于临界资源，它们都要求被互斥地共享。

2) 同时访问方式
系统中还有另一类资源，允许在一段时间内由多个进程“同时”对它们进行访问。
这里所谓的“同时”往往是宏观上的，而在微观上，
这些进程可能是交替地对该资源进行访问即 “分时共享”。
典型的可供多个进程“同时”访问的资源是磁盘设备，
一些用重入码编写的文件也可以被“同时”共享，即若干个用户同时访问该文件。

并发和共享是操作系统两个最基本的特征，这两者之间又是互为存在条件的：
资源共享是以程序的并发为条件的，若系统不允许程序并发执行，
则自然不存在资源共享问题；
若系统不能对资源共享实施有效的管理，
也必将影响到程序的并发执行，甚至根本无法并发执行。
   

    虛拟（Virtual)
虚拟是指把一个物理上的实体变为若干个逻辑上的对应物。
物理实体（前者）是实的，即实际存在的；
而后者是虚的，是用户感觉上的事物。
用于实现虚拟的技术，称为虚拟技术。在操作系统中利用了多种虚拟技术，
分别用来实现(虚拟处理器)、(虚拟内存)和(虚拟外部设备)等。
在虚拟处理器技术中，是通过多道程序设计技术，让多道程序并发执行的方法，
来分时使用一个处理器的。此时，虽然只有一个处理器，
但它能同时为多个用户服务，
使每个终端用户都感觉有一个中央处理器（CPU)在专门为它服务。
利用多道程序设计技术，把一个物理上的CPU虚拟为多个逻辑上的CPU,
称为虚拟处理器。

类似地，可以通过虚拟存储器技术，将一台机器的物理存储器变为虚拟存储器，
以便从逻辑上来扩充存储器的容量。
当然,这时用户所感觉到的内存容量是虚的。
我们把用户所感觉到的存储器（实际是不存在的）称为虚拟存储器。

还可以通过虚拟设备技术，将一台物理I/O设备虚拟为多台逻辑上的I/O设备，
并允许每个用户占用一台逻辑上的I/O设备，
这样便可以使原来仅允许在一段时间内由一个用户访问的设备（即临界资源)，
变为在一段时间内允许多个用户同时访问的共享设备。
因此，操作系统的虚拟技术可归纳为：时分复用技术，如处理器的分时共享；
空分复用技术，如虚拟存储器（注：学到后续内容再慢慢领悟)。
      
	  
	  
	  异步(Asynchronism)
在多道程序环境下，允许多个程序并发执行，但由于资源有限，
进程的执行不是一贯到底，而是走走停停，以不可预知的速度向前推进，
这就是进程的异步性。

异步性使得操作系统运行在一种随机的环境下，
可能导致进程产生与时间有关的错误 
(就像对全局变量的访问顺序不当会导致程序出错一样）。
但是只要运行环境相同，操作系统必须保证多次运行进程，
都获得相同的结果。后面会深入讨论。



*********************************************************************



为了给多道程序提供良好的运行环境，操作系统应具有以下几方面的功能：
	处理器管理、 存储器管理、设备管理和文件管理。
	为了方便用户使用操作系统，还必须向用户提供接口。
同时操作系统可用来扩充机器，以提供更方便的服务、更高的资源利用率。

操作系统作为计算机系统资源的管理者

1) 处理器管理
在多道程序环境下，处理器的分配和运行都以进程（或线程）为基本单位，
因而对处理器的管理可归结为对进程的管理。
并发时在计算机内同时运行多个进程，所以，进程何时创建、
何时撤销、如何管理、如何避免冲突、.合理共享就是进程管理的最主要的任务。
进程管理的主要功能有：进程控制、进程同步、
进程通信、死锁处理、处理机调度等。

2) 存储器管理
存储器管理是为了给多道程序的运行提供良好的环境，
方便用户使用以及提高内存的利用率，主要包括内存分配、地址映射、
内存保护与共享和内存扩充等功能。

3) 文件管理
计算机中的信息都是以文件的形式存在的，
操作系统中负责文件管理的部分称为文件系统。
文件管理包括文件存储空间的管理、目录管理及文件读写管理和保护等。

4) 设备管理
设备管理的主要任务是完成用户的I/O请求，
方便用户使用各种设备，并提高设备的利用率，主要包括缓冲管理、
设备分配、设备处理和虛拟设备等功能。



操作系统作为用户与计算机硬件系统之间的接口

为方便用户使用计算机，操作系统还提供了用户接口。
操作系统提供的接口主要分为两类•• 一类是命令接口，
用户利用这些操作命令来组织和控制作业的执行；另一类是程序接口，
编程人员可以使用它们来请求操作系统服务。

1) 命令接口
使用命令接口进行作业控制的主要方式有两种，
即联机控制方式和脱机控制方式。按作业控制方式的不同，
可以将命令接口分为联机命令接口和脱机命令接口。

联机命令接口又称交互式命令接口，适用于分时或实时系统的接口。
它由一组键盘操作命令组成。用户通过控制台或终端输入操作命令，
向系统提出各种服务要求。用户每输入完一条命令，
控制权就转入操作系统的命令解释程序，
然后由命令解释程序对输入的命令解释并执行，完成指定的功能。
之后，控制权又转回到控制台或终端，此时用户又可以输入下一条命令。

脱机命令接口又称批处理命令接口，即适用于批处理系统，
它由一组作业控制命令（或称作业控制语句）组成。
脱机用户不能直接干预作业的运行，
应事先用相应的作业控制命令穹成一份作业操作说明书，
连同作业一起提交给系统。当系统调度到该作业时，
由系统中的命令解释程序对作业说明书上的命令或作业控制语句遂条解释执行，
从而间接地控制作业的运行。

2) 程序接口

程序接口由一组系统调用命会（简称系统调用，也称广义指令）组成。
用户通过在程序中使用这些系统调用命令来请求操作系统为其提供服务。
用户在程序中可以直接使用这组系统调用命令向系统提出各种服务要求，
如使用各种外部设备，进行有关磁盘文件的操作，
申请分配和回收内存以及其他各种控制要求。

而当前最为流行的是图形用户界面(GUI)即图形接口，用户通过鼠标和键盘，
在图形界面上单击或使用快捷键就能很方便地使用操作系统。
有些系统提供了上述三种接口，但 GUI 最终是通过调用程序接口实现的，
严格地说它不属于操作系统的一部分。
操作系统用做扩充机器

没有任何软件支持的计算机称为裸机，它仅构成计算机系统的物质基础，
而实际呈现在用户面前的计算机系统是经过若干层软件改造的计算机。
裸机在最里层，它的外面是操作系统，
由操作系统提供的资源管理功能和方便用户的各种服务功能，
将裸机改造成功能更强、 使用更方便的机器，
通常把覆盖了软件的机器称为扩充机器，又称之为虚拟机。


****************************************************************

计算机系统中，通常CPU执行两种不同性质的程序：
一种是操作系统内核程序；另一种是用户自编程序或系统外层的应用程序。
对操作系统而言，这两种程序的作用不同，前者是后者的管理者，
因此“管理程序”要执行一些特权指令，
而“被管理程序”出于安全考虑不能执行这些指令。
所谓特权指令，是指计算机中不允许用户直接使用的指令，
如(I/O指令)、 置(中断指令)，存取用于内存保护的(寄存器)、
送程序状态字到程序(状态字寄存器)等指令。
操作系统在具体实现上划分了用户态（目态）和内核态（管态)，
以严格区分两类程序。

内核是计算机上配置的底层软件
1) 时钟管理  时钟的第一功能是计时，操作系统需要通过时钟管理，
   向用户提供标准的系统时间  通过时钟中断的管理，可以实现进程的切换
   按截止时间控制运行的实现；在批处理系统中，
   通过时钟管理来衡量一个作业的运行程度等
2) 中断机制   是提高多道程序运行环境中CPU的利用率，
   而且主要是针对外部设备的  键盘或鼠标信息的输入、进程的管理和调度、
   系统功能的调用、设备驱动、文件访问等，无不依赖于中断机制。
   可以说，现代操作系统是靠中断驱动的软件
3) 原语  系统中的设备驱动、CPU切换、
	  进程通信等功能中的部分操作都可以定义为原语
4) 系统控制的数据结构及处理
系统中用来登记状态信息的数据结构很多，比如作业控制块、进程控制块(PCB)、
设备控制块、各类链表、消息队列、缓冲区、空闲区登记表、内存分配表等。
为了实现有效的管理，系统需要一些基本的操作，常见的操作有以下三种：
  进程管理：进程状态管理、进程调度和分派、创建与撤销进程控制块等。
  存储器管理：存储器的空间分配和回收、内存信息保护程序、代码对换程序等。
  设备管理：缓冲区管理、设备分配和回收等。
************************************************************

  在操作系统中引入核心态和用户态这两种工作状态后，
 就需要考虑这两种状态之间如何切换。操作系统内核工作在核心态，
 而用户程序工作在用户态。但系统不允许用户程序实现核心态的功能，
 而它们又必须使用这些功能。因此，需要在核心态建立一些“门”，
 实现从用户态进入核心态。在实际操作系统中，
 CPU运行上层程序时唯一能进入这些“门”的途径就是通过中断或异常。
 
 在操作系统中引入核心态和用户态这两种工作状态后，
 就需要考虑这两种状态之间如何切换。操作系统内核工作在核心态，
 而用户程序工作在用户态。
 当中断或异常发生时，运行用户态的CPU会立即进入核心态，
 这是通过硬件实现的
 （例如，用一个特殊寄存器的一位来表示CPU所处的工作状态，
  0 表示核心态，1 表示用户态。若要进入核心态，只需将该位置0即可)。
中断是操作系统中非常重要的一个概念，
对一个运行在计算机上的实用操作系统而言，
缺少了中断机制，将是不可想象的。 
 
  中断(Interruption)，也称外中断，指来自CPU执行指令以外的事件的发生，
如设备发出的I/O结束中断，表示设备输入/输出处理已经完成，
希望处理机能够向设备发下一个输入 / 输出请求，
同时让完成输入/输出后的程序继续运行。
时钟中断，表示一个固定的时间片已到，让处理器处理计时、
启动定时运行的任务等。这一类中断通常是与当前程序运行无关的事件，
即它们与当前处理机运行的程序无关。

  异常(Exception)，也称内中断、例外或陷入(Trap)，
指源自CPU执行指令内部的事件，如程序的(非法操作码)、 (地址越界)、
(算术溢出)、(虚存系统的缺页)以及(专门的陷入指令)等引起的事件。
对异常的处理一般要依赖于当前程序的运行现场，而且异常不能被屏蔽，
一旦出现应立即处理。
******************************************************************





