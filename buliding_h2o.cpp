// class H2O {
//     int d; // H - 2 * O
//     std::mutex mtx;
//     std::condition_variable cv;
    
// public:
//     H2O(): d(0) {
        
//     }

//     void hydrogen(function<void()> releaseHydrogen) {
//         unique_lock<std::mutex> lck(mtx);
//         while (d >= 2) {
//             cv.wait(lck);
//         }
//         // releaseHydrogen() outputs "H". Do not change or remove this line.
//         releaseHydrogen();
//         d++;
//         cv.notify_all();
//     }

//     void oxygen(function<void()> releaseOxygen) {
//         unique_lock<std::mutex> lck(mtx);
//         while (d < 0) {
//             cv.wait(lck);
//         }
//         // releaseOxygen() outputs "O". Do not change or remove this line.
//         releaseOxygen();
//         d-=2;
//         cv.notify_all();
//     }
// };

// easy one updated

class H2O {
    std::mutex mtx;
    std::condition_variable cv;
    int turn;
public:
    H2O() {
        turn = 0;
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<std::mutex> lck(mtx);
        while ( turn == 2) {
            cv.wait(lck);
        }
        
        releaseHydrogen();
        ++turn;
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<std::mutex> lck(mtx);
        while (turn < 2) {
            cv.wait(lck);
        }
        releaseOxygen();
        turn = 0;
        cv.notify_all();
    }
};