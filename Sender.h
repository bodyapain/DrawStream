#pragma once
#include <boost/asio.hpp>
#include <iostream>
class Sender
{
public:
	Sender() : socket(io_context) {}
	~Sender() 
	{
		boost::system::error_code ec;
		socket.close(ec);
	}

	void connectToServer(const std::string& host, const std::string& port) 
	{
		boost::asio::ip::tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(host, port);

		boost::asio::connect(socket, endpoints);
		std::cout << "Connected to " << host << ":" << port << "\n";
	}

	void send() 
	{
		boost::asio::async_write(socket, buffers,
			[](boost::system::error_code ec, size_t length) {
				if (!ec) std::cout << "Image sent successfully!\n";
			});
		io_context.run();
	}
	void prepareBuffers(const char* pixelData, uint32_t imageSize) 
	{
		// Очищаем старые буферы
		buffers.clear();

		// Добавляем заголовок с размером (важно для приёмника)
		uint32_t sizeNetworkOrder = htonl(imageSize);  // сетевой порядок байт
		buffers.push_back(boost::asio::buffer(&sizeNetworkOrder, sizeof(sizeNetworkOrder)));

		// Добавляем сами пиксели
		buffers.push_back(boost::asio::buffer(pixelData, imageSize));
	}

private:
	std::vector<boost::asio::const_buffer> buffers;
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::socket socket;
	std::jthread send_thread;
};

