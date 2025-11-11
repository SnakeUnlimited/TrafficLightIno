
#include "TL_Test.h"
#include "QueueInt.h"


class TQueueInt : public TL_Test {

public:
    bool exec() override {
        QueueInt queue;
        Tprint("\nTQueueInt Test: Size=");
        Tprint(queue.itemCount());
        Tprint("\n");
        for (int i=1; i < 13; i++) {
            Tprint("Enq: Size= ");
            Tprint(queue.itemCount());
            Tprint(" // Insert: ");
            Tprint(i);
            Tprint("\n");
            queue.enqueue(i);
            if (queue.itemCount() != i) {
                Tprint("itemCount passt nicht");
                return false;
            }
        }
        int amount = 12;
        for (int i=1; i < 13; i++) {
            if (amount != queue.itemCount()) {
                Tprint("Queue Amount passt nicht");
                return false;
            }
            amount--;
            int pre = queue.getHead();
            int res = queue.dequeue();
           // Tprintln("Deq: Head: "+String(pre)+" // dequeued: "+String(res));
            Tprint("Deq Head: ");
            Tprint(pre);
            Tprint(" // ");
            Tprint(res);
            Tprint("\n");
            if (pre != res) {
                Tprint("Deq: Pre und Res unterschiedlich")
                return false;
            }
        }
        return true;
    }
};