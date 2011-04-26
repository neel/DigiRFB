#ifndef REQUESTMONITOR_H
#define REQUESTMONITOR_H

namespace DG{
	class ClientSocket;
	class MatrixStorage;
}

namespace DG{
class RequestMonitor{
	private:
		DG::ClientSocket* socket;
		DG::MatrixStorage* storage;
	private:
		static bool _instantiated;
		static RequestMonitor* monitor;
	public:
		static RequestMonitor& instance(DG::ClientSocket* socket, DG::MatrixStorage* storage);
	private:
		RequestMonitor();
		void setResource(DG::ClientSocket* _socket, DG::MatrixStorage* _storage);
		RequestMonitor(const RequestMonitor&);
		void operator=(const RequestMonitor&);
	private:
		static int reqCount;
		static int rectCount;
	public:
		void rectAdded();
		void request();
	private:
		void _send();
};
}
#endif // REQUESTMONITOR_H
