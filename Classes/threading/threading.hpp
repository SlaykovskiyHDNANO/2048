#pragma once
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <memory>

namespace utils {
	namespace threading {

		template<typename T>
		class ThreadMessageQueue  {
			class Values {
			public:
				std::condition_variable event;
				mutable std::mutex		conlock;
				mutable std::unique_lock<std::mutex> cu;
				mutable std::mutex		lock;
				bool					notified;
				bool					hasnew;
				std::queue<T>			queue;

				Values() :event(), conlock(), lock(), notified(false), hasnew(false), queue(){ /*cu = std::unique_lock<std::mutex>(this->conlock);*/ };
			};
		protected:
			std::shared_ptr<Values> vals;
			
		private:
			void empty(){
				std::queue<T> empty;
				std::swap(reinterpret_cast<std::queue<T>>(this->vals->queue), empty);
			}
			
		public:
			ThreadMessageQueue<T>():vals(new Values()) {
			};
			//DANGEROUS

			ThreadMessageQueue<T>(const ThreadMessageQueue& msg) : vals(msg.vals)
			{
				//this->vals->conlock		= std::mutex();
				//this->vals->lock		= std::mutex();
				//this->vals->cu = std::unique_lock<std::mutex>(this->vals->conlock);
			}
			ThreadMessageQueue<T>& operator=(const ThreadMessageQueue<T>& msg){
				this->vals = msg.vals;
				return *this;
			}
			size_t size(){
				return this->vals->queue.size();
			}
			void pop() {
				//lock thread
				this->vals->lock.lock();
				if (this->vals->hasnew) {
					this->vals->queue.pop();
					this->vals->hasnew = this->size() > 0;
					this->vals->lock.unlock();

				}
				else {
					this->vals->lock.unlock();
					throw std::exception("Queue is empty", 1);
				}

			};
			T first() {
				//lock thread
				this->vals->lock.lock();
				if (this->hasnew) {
					//return first element
					T res = this->vals->queue.front();
					this->vals->lock.unlock();
					return res;
				}
				else {
					this->vals->lock.unlock();
					throw std::exception("Queue is empty.", 1);
				}
			};
			void push(const T& value) {
				//lock thread
				this->vals->lock.lock();
				//return first element
				this->vals->queue.push(value);
				this->vals->lock.unlock();
				std::unique_lock<std::mutex> ll(this->vals->conlock);
				this->vals->event.notify_one();
				this->vals->hasnew = true;
				this->vals->notified = true;
				//ll.unlock();
				//ll.release();
			};

			T fpop()
			{
				this->vals->lock.lock();
				if (this->vals->hasnew) {
					T res = this->vals->queue.front();
					this->vals->queue.pop();
					this->vals->hasnew = this->size() > 0;
					this->vals->lock.unlock();
					return res;
				}
				else {
					this->vals->lock.unlock();
					throw std::exception("Queue is empty.", 1);
				}
			}

			bool has_new() {
				//надо ли здесь лочить? Наверное, нет
				return this->vals->hasnew;
			};
			bool wait(){
				//if queue is still has messages
				this->vals->lock.lock();
				if (this->vals->hasnew) {
					this->vals->notified = false;
					this->vals->lock.unlock();
					return true;
				}
				else
					this->vals->lock.unlock();
				std::unique_lock<std::mutex> ll(this->vals->conlock);
				
				while (!this->vals->notified)
					this->vals->event.wait(ll);
				
				this->vals->notified = false;
				//ll.unlock();
				//ll.release();
				return true;
			}

			bool wait(const int msec) {
				//if queue is still has messages
				this->vals->lock.lock();
				if (this->vals->hasnew) {
					this->vals->lock.unlock();
					return true;
				}
				else
					this->vals->lock.unlock();
				//else
				std::mutex lock;
				std::unique_lock<std::mutex> ll(this->vals->conlock);

				std::cv_status timeout = std::cv_status::no_timeout;
				while (!this->vals->notified && timeout == std::cv_status::no_timeout)
						timeout = this->vals->event.wait_for(ll, std::chrono::milliseconds(msec));
				this->vals->lock.lock();
				auto ret = this->vals->notified;
				this->vals->notified = false;
				this->vals->lock.unlock();
				//ll.unlock();
				//ll.release();
				return  ret;
			};

		};


		bool KillNativeThread(std::thread::native_handle_type handle);

	}
}