#include <stdio.h> // For printf
#include <concord/discord.h> // Core Concord API
#include <string.h> // For strcmp (command checking)

void on_ready(struct discord *client __attribute__ ((unused)),
	      const struct discord_ready *event)
{
	printf("Bot logged in as %s#%s.\n", // Prints bot's username to terminal on launch.
	       event->user->username,
	       event->user->discriminator);
}

int main()
{
	struct discord *client = discord_config_init("config.json"); // This function reads the JSON file, extracts the token, sets up logging, and creates the client struct.
	discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT); // For text commands.
	discord_set_on_ready(client, &on_ready); // Registers the callback.
	discord_run(client); // Connects to Discord's Gateway, authenticates with the token, and enters the asynchronous event loop (blocking until shutdown).
}

