// FishManager

#ifndef _FishManager
#define _FishManager

class SurrealSprite;

class FishManager
{
	friend class SceneOne;
	friend class SceneTwo;
private:
	static FishManager* ptrInstance;

	FishManager();
	FishManager(const FishManager& c) = delete;
	FishManager& operator = (const FishManager& t) = delete;
	~FishManager() = default;

	static FishManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new FishManager;
		return *ptrInstance;
	};

public:
	static void LoseHeart() { Instance().privLoseHeart(); };
	static int GetHeartCount() { return Instance().privGetHeartCount(); };
	static void GainHeart() { Instance().privGainHeart(); };
	static void SetHearts(int hearts) { Instance().privSetHearts(hearts); };

private:

	void privDelete();
	static void Delete() { Instance().privDelete(); };
	void privNoHearts();
	static void NoHearts() { Instance().privNoHearts(); };

	void privLoseHeart();
	int privGetHeartCount();

	void privGainHeart();
	void privSetHearts(int hearts);

	int maxHearts = 3;
	int currentHearts;

};

#endif _FishManager