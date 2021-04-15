
struct Task
{
	char description[100];
	bool active;
};

struct CompiledTasks {
	struct Task Tasks[10];
};

void TaskManagerSave(struct CompiledTasks SaveData);
struct CompiledTasks TaskManagerLoad();