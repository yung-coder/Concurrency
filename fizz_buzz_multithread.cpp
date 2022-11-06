class FizzBuzz {
private:
    int n;
    mutex m;
    condition_variable cv;
    int i;
    
/* all the threads will share the same "i" therefore the 
loop variable "i" should be synchronised in a way that 
only one thread should access critical section at a given 
time  because  critical section contains i  
and scheduling should be done to avoid race  condition 
and also mutual exclusion  should be kept in mind

*/
public:
    FizzBuzz(int n) {
        this->n = n;
        this->i=1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
         while(i<=n){
             unique_lock<mutex> lock (m);
             
             // if the condition "i is divisible by 3 and not 5" is not true , therefore it will wait 
             while(i<=n && ( i%3==0 && i%5!=0) == 0)  
                 cv.wait(lock);
             
             // i is divisible by 3 and not 5 , therefore we will print "fizz"
             // and increament i
             if(i<=n){
                 printFizz();
                 ++i;
             }
             
             // now notify the threads which were waiting , so that they can resume 
             cv.notify_all();
         }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
         while(i<=n){
             unique_lock<mutex> lock (m);
             // if the condition "i is divisible by 5 and not 3" is not true , therefore it will wait 
             while(i<=n && ( i%3!=0 && i%5==0) == 0)
                 cv.wait(lock);
             
             // i is divisible by 5 and not 3, therefore we will print "buzz"
             // and increament i
             if(i<=n){
                 printBuzz();
                 ++i;
             }
             
             // now notify the threads which were waiting , so that they can resume 
             cv.notify_all();
         }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
         while(i<=n){
             unique_lock<mutex> lock (m);
              // if the condition "i is divisible by 3 and 5" is not true , therefore it will wait 
             while(i<=n && ( i%3==0 && i%5==0) == 0)
                 cv.wait(lock);
             
             // i is divisible by 5 and  3, therefore we will print "fizzbuzz"
             // and increament i
             if(i<=n){
                 printFizzBuzz();
                 ++i;
             }
             
              // now notify the threads which were waiting , so that they can resume 
             cv.notify_all();
         }
    }