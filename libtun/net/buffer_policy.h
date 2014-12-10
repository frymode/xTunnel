#pragma once

namespace xTunnel
{
	class BufferPolicy
	{
	public:
		BufferPolicy(int initial_size = 4096);

        int GetSize() const;
		void SetUsedSize(int size);

	private:
		int size_;
	};
}