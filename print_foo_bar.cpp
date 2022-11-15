class FooBar {
private:
    int n;
    std::mutex mtx;
    std::condition_variable cv;
    bool turn;

public:
    FooBar(int n) {
        this->n = n;
        turn =0;
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            while(turn ==1 ){
                cv.wait(lock);
            }
        	printFoo();
            turn =1;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) { 
           for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            while(turn ==0 ){
                cv.wait(lock);
            }
        	printBar();
            turn =0;
            cv.notify_all();
        }
    }
};