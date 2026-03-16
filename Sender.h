#pragma once
#include <boost/asio.hpp>
#include <iostream>
class Sender
{
public:
	Sender() : socket(io_context),
		work_guard(boost::asio::make_work_guard(io_context)) {}
	~Sender() 
	{
		work_guard.reset();
		io_context.stop();

		boost::system::error_code ec;
		socket.close(ec);

		if (send_thread.joinable())
			send_thread.join();
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
		if (!buffers.empty())
		{
			boost::asio::async_write(socket, buffers,
				[](boost::system::error_code ec, size_t length) {
					if (!ec) std::cout << "Image sent successfully!\n";
				});
		}
	}

	void startStream()
	{
		send_thread = std::jthread([this]() {
					io_context.run();
			});
	}

	void prepareBuffers(std::vector<char> pixelData, uint32_t imageSize)
	{
		if (!pixelData.empty()) {
			if (!localPixelData.empty())
			{
				localPixelData.clear();
			}
			localPixelData = pixelData;
			localImageSize = imageSize;
			buffers.clear();
			headerValue = htonl(imageSize);
			buffers.push_back(boost::asio::buffer(&headerValue, sizeof(headerValue)));
			buffers.push_back(boost::asio::buffer(localPixelData, localImageSize));
		}
	}

private:

	boost::asio::io_context io_context;
	boost::asio::ip::tcp::socket socket;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard;

	std::vector<boost::asio::const_buffer> buffers;
	std::vector<char> localPixelData;
	uint32_t localImageSize;
	uint32_t headerValue;

	std::jthread send_thread;
};

