#ifdef WIN32
#include <wtypes.h>
#endif

namespace API
{
	class API
	{
	public:
		static void Init(std::string executingFilePath);
	private:
		static std::string executingDirectory;
#ifdef WIN32
		static HMODULE hEngine;
#endif // DEBUG
		static void LoadEngine();
	};
}