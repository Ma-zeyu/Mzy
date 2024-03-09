# C++进程与线程

线程和进程：一个进程会被分为多个线程，线程是进程的单元

API:可以包括不同的操作、函数或指令集合，可以理解为是一种承载命令的载体，实现交互。

C++11 新标准中引入了5个头文件来支持多线程编程

## #include < thread>

### 1.多进程并发

多进程的并发不是一个好的选择

### 2.多线程并发

同一进程中的多个线程共享相同的地址空间，可以访问进程中的大部分数据，指针和引用可以在线程间进行传递

没有操作系统的保护，需要程序员做的事情多

#### 2.1创建线程

把函数添加到线程当中即可。               **线程一旦被创建就会运行，无需调用。**

```cpp
std::thread myThread ( thread_fun);//函数形式为void thread_fun()
myThread.join();
//同一个函数可以代码复用，创建多个线程
```

thread是一个类，myThread是一个实例化对象，myThread.join()是类内函数，表示线程工作的方法

也就是说，有一个线程是myThread，并通过构造函数将thread_fun放到线程中去

#### 2.2join和detach

join: 表示主线程在这里会等待 `myThread` 线程执行完毕后再继续执行后续的代码。

detach：用于将线程与 `std::thread` 对象分离。当调用 `detach()` 方法时，该线程会继续独立运行，与 `std::thread` 对象解绑，使得 `std::thread` 对象不再与线程相关联。这意味着主线程不再需要等待该线程执行完毕。一旦线程被分离，程序员就失去了对该线程的控制，线程的资源管理和生命周期将由操作系统来处理。主线程不会等待子线程结束。如果主线程运行结束，程序则结束。

没有join和detach会造成内存泄漏，程序终止。

**join和detach是说明子线程与主线程之间的关系。**

**不要在乎join和detach的位置**

#### 2.3this_thread

this_thread是一个类，它有4个功能函数，无需创建对象，具体如下：

函数	                     使用	                                                                             说明
get_id	        std::this_thread::get_id()	                                                获取线程id
yield	          std::this_thread::yield()	                                     放弃线程执行，回到就绪状态
sleep_for	  std::this_thread::sleep_for(std::chrono::seconds(1));	暂停1秒
sleep_until	          如下	                                                                  一分钟后执行，如下

```cpp
using std::chrono::system_clock;
std::time_t tt = system_clock::to_time_t(system_clock::now());

struct std::tm * ptm = std::localtime(&tt);
cout << "Waiting for the next minute to begin...\n";
++ptm->tm_min; //加一分钟
ptm->tm_sec = 0; //秒数设置为0
//暂停执行，到下一整分执行
this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
```

## #include< mutex>

当多个线程访问公共资源时，会出现不安全的现象，需要对不安全的代码段进行保护，使用到mutex

### 1.lock与unlock

加锁后，其他线程无法对其访问。

```cpp
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex

std::mutex mtx;          // mutex for critical section

void print_block (int n, char c) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  mtx.lock();
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
  mtx.unlock();
}

int main ()
{
  std::thread th1 (print_block,50,'*');//线程1：打印*
  std::thread th2 (print_block,50,'$');//线程2：打印$

  th1.join();
  th2.join();

  return 0;
}
```

lock与unlock间，程序退出，或者上锁顺序不同，会产生死锁现象（只有上锁，没有解锁）

### 2.lock_guard  //模版类

解决死锁问题

特点：

- 创建即加锁，**作用域结束自动析构并解锁**，无需手工解锁

- **不能中途解锁**，必须等作用域结束才解锁

- 不能复制

  ```cpp
  #include <thread>
  #include <mutex>
  #include <iostream>
  
  int g_i = 0;
  std::mutex g_i_mutex;  // protects g_i，用来保护g_i
  
  void safe_increment()
  {
      const std::lock_guard<std::mutex> lock(g_i_mutex);
      ++g_i;
      std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
      // g_i_mutex自动解锁
  }
  
  int main()
  {
  	std::cout << "main id: " <<std::this_thread::get_id()<<std::endl;
      std::cout << "main: " << g_i << '\n';
  
      std::thread t1(safe_increment);
      std::thread t2(safe_increment);
  
      t1.join();
      t2.join();
  
      std::cout << "main: " << g_i << '\n';
  }
  ```

  ### 3.unique_lock    //模版类

  unique_lock是lock_guard的加强版

**特点：**

- 创建时可以不锁定（通过指定第二个参数为std::defer_lock），而在需要时再锁定
- **可以随时加锁解锁**
- **作用域规则同 lock_grard，析构时自动释放锁**
- 不可复制，可移动
- 条件变量需要该类型的锁作为参数（此时必须使用unique_lock）

unique_lock两个参数

```cpp
std::lock_guard<std::mutex> sbguard1(my_mutex1, std::adopt_lock);// std::adopt_lock标记作用；
```

```cpp
//第二个参数
std::adopt_lock  //表示这个互斥量已经被lock了（你必须要把互斥量提前lock了 ，否者会报异常）
std::try_to_lock  //我们会尝试用mutex的lock()去锁定这个mutex,但如果没有锁定成功，我也会立即返回，并不会阻塞在那里；
                   //用这个try_to_lock的前提是你自己不能先lock。
std::defer_lock   //前提是，你不能自己先lock,否则会报异常,初始化了一个没有加锁的mutex
```

```cpp
//成员函数
lock()     //加锁
unlock()  //解锁
try_lock()  //尝试给互斥量加锁，如果拿不到锁，返回false,如果拿到了锁，返回true,这个函数是不阻塞的；
release() //返回它所管理的mutex对象指针，并释放所有权；也就是说，这个unique_lock和mutex不再有关系。
```

## Conditional variable条件变量

**目的**：条件变量的主要目的是允许一个或多个线程在某些条件成立之前**等待**。（用于堵塞某些线程）一旦条件成立，一个或多个正在等待的线程可以被**唤醒。**

**核心操作**：等待与唤醒

通常结合mutex一起使用,条件满足开锁mutex

条件变量的条件只有真和假

```cpp
//下面是一些函数
//初始化条件变量
pthread_cond_init
//阻塞等待
pthread_cond_wait
//超时等待
pthread_cond_timewait
//唤醒一个等待该条件的线程
pthread_cond_signal
//唤醒全部等待该条件的所有线程
pthread_cond_broadcast
//销毁条件变量
pthread_cond_destroy
```

## shared_lock和shared_mutex读写锁

一个用于同步访问的机制，允许多个读取者同时访问同一资源，但在任何时候只允许一个写入者。

使用 `pthread_rwlock_t` 类型的变量表示读写锁，使用 `pthread_rwlock_init` 来初始化或者PTHREAD_RWLOCK_INITIALIZER初始化静态的锁，`pthread_rwlock_destroy` 来销毁。

pthread_rwlock_rdlock：获取读锁。如果有其他线程持有写锁，或者有其他线程正在等待获取写锁，那么这个函数会阻塞，直到可以安全地获取读锁为止。

pthread_rwlock_wrlock：获取写锁。如果有其他线程持有读锁或写锁，那么这个函数会阻塞，直到可以安全地获取写锁为止。

pthread_rwlock_unlock：释放读锁或写锁。
```cpp
#include <pthread.h>

pthread_rwlock_t lock;

void read_data() {
    pthread_rwlock_rdlock(&lock);
    // 读取数据的代码
    pthread_rwlock_unlock(&lock);
}

void write_data() {
    pthread_rwlock_wrlock(&lock);
    // 写入数据的代码
    pthread_rwlock_unlock(&lock);
}
```

函数原型

```cpp
//创建读写锁
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
                        const pthread_rwlockattr_t *restrict attr);
//销毁读写锁
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
//获取读锁
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
//获取写锁
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
//解锁
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
```

实例

```cpp
#include <pthread.h>
#include <stdio.h>

#define NUM_READER_THREADS 5

pthread_rwlock_t rwlock;
int counter = 0; // 共享资源

void *reader(void *arg) {
    pthread_rwlock_rdlock(&rwlock);
    printf("Reader: counter = %d\n", counter);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void *writer(void *arg) {
    pthread_rwlock_wrlock(&rwlock);
    counter++;
    printf("Writer: counter = %d\n", counter);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main() {
    pthread_t reader_threads[NUM_READER_THREADS], writer_thread;

    pthread_rwlock_init(&rwlock, NULL);

    pthread_create(&writer_thread, NULL, writer, NULL);
    for (int i = 0; i < NUM_READER_THREADS; i++) {
        pthread_create(&reader_threads[i], NULL, reader, NULL);
   }

   pthread_join(writer_thread, NULL);
    for (int i = 0; i < NUM_READER_THREADS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
```



带超时功能的读写锁

```cpp
int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rwlock,
                               const struct timespec *restrict abs_timeout);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict rwlock,
                               const struct timespec *restrict abs_timeout);
```





