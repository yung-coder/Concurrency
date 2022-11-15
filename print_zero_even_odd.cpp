class ZeroEvenOdd {
private:
    int n, counter;
    int state, prev_state;
    
    mutex mtx;
    condition_variable cv;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        counter = 1;
        state = 0;
        prev_state = 2;
    }

    void zero(function<void(int)> printNumber) {
        while(1){
            unique_lock<mutex> lck(mtx);
            
            while(counter <= n && state != 0)
                cv.wait(lck);

            if (counter > n)    return;

            printNumber(0);
            state = prev_state == 2 ? 1 : 2;
            cv.notify_all();
        }
        
    }

    void even(function<void(int)> printNumber) {
        while(1){
            unique_lock<mutex> lck(mtx);
            
            while(counter <= n && state != 2)
                cv.wait(lck);
            
            if (counter > n)    return;
            printNumber(counter++);

            state = 0;
            prev_state = 2;
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while(1){
            unique_lock<mutex> lck(mtx);
            
            while(counter <= n && state != 1)
                cv.wait(lck);
            
            if (counter > n)    return;

            printNumber(counter++);
            state = 0;
            prev_state = 1;
            cv.notify_all();
        }
    }
};