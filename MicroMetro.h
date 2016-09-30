#pragma once

class MicroMetro
{
public:
    MicroMetro(unsigned long interval_micros, uint8_t autoreset = true)
    {
        this->autoreset = autoreset;
        interval(interval_micros);
        reset();
    }
    void interval(unsigned long interval_micros)
    {
        	this->interval_micros = interval_micros;
    }
    bool check()
    {
        if (!b_running) return false;
        if (micros() - previous_micros >= interval_micros)
        {
            if (this->interval_micros <= 0 || this->autoreset ) {
              this->previous_micros = micros();
            } else {
              this->previous_micros += this->interval_micros;
            }
          return true;
      }
      return false;
    }

    void reset()
    {
        this->previous_micros = micros();
    }

    void start()
    {
        b_running = true;
        reset();
    }

    void restart()
    {
        b_running = true;
        start();
        reset();
    }

    unsigned long read()
    {
        if (!b_running) return 0;
        return micros() - previous_micros;
    }

    unsigned long read_ms()
    {
        return read() / 1000;
    }

    void stop()
    {

        b_running = false;
    }

    bool isRunning() { return b_running; }

private:
    bool autoreset;
    unsigned long  previous_micros, interval_micros;
    bool b_running;
};
