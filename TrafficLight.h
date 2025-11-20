
#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#define LIGHT_STOP 0
#define LIGHT_PREPARE 1
#define LIGHT_MOVE 2
#define LIGHT_WAIT 3

#define LIGHT_TICK_AMOUNT 3
#define LIGHT_QUEUE_AMOUNT 9

class TrafficLight {

private:
  QueueInt _statusQueue;

  int _currentStatus;
  int _currentDuration;
  int _amount;
  bool _isMove;

  virtual void _setStatus(int status) = 0; // Turn on individual LEDs
public:

  TrafficLight() {
    this->_currentStatus = 0;
    this->_currentDuration = 0;
    this->_amount = 0;
    this->_isMove = false;
  }

  bool getIsMove() { return _isMove; }
  int getCurrentStatus() { return _currentStatus; }
  
  void setStatus(int status) {
    if (status > 0 && status < 4) {
      _setStatus(status);
    }
  }

  void toggle() {
    return toggle(!getIsMove());
  }

  void toggle(bool isMove) {
      if (_isMove == isMove) { return; }
      if (_amount >= LIGHT_QUEUE_AMOUNT - 2) { 
        Dprintln("TrafficLight: TOGGLE Too much bro ("+toString()+")\n");
        return;
      }
      // Rot -> Grün
      if (isMove) {
        _statusQueue.enqueue(1);
        _statusQueue.enqueue(2);
       // Dprintln(toString()+" // -> Added Red2Green");
      }
      // Grün -> Rot 
      else {
        _statusQueue.enqueue(3);
        _statusQueue.enqueue(0);
        //Dprintln(toString()+" // -> Added Green2Red");
        
      }
      if (_amount <= 0) {
        _currentDuration = LIGHT_TICK_AMOUNT;
        
      }
      _isMove = isMove;
      _amount += 2;
  }

  void tick() {
    //Dprint(toString()+" \t\t\t\t");
    if (_statusQueue.isEmpty()) { return; }
    _currentDuration--;
    if (_currentDuration > 0) { return; }
    // ** TICK **
    _currentDuration = LIGHT_TICK_AMOUNT;
    _currentStatus = _statusQueue.dequeue();
    _amount--;
    _setStatus(_currentStatus);
  }

  virtual String toString() = 0;
};

#endif