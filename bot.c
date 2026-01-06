#include <stdio.h> // For printf
#include <concord/discord.h> // Core Concord API
#include <string.h> // For strcmp (command checking)

void on_ready(struct discord *client __attribute__ ((unused)), const struct discord_ready *event)
{
	printf("Bot logged in as %s#%s.\n", // Prints bot's username to terminal on launch.
	       event->user->username,
	       event->user->discriminator);
}

void on_message(struct discord *client __attribute__((unused)), const struct discord_message *event)
{
	if (event->author->bot) return; // Checks if author is bot.
	if (strcmp(event->content, "ping") == 0) // Checks if message says ping.
	{	
	        struct discord_create_message params = { .content = "pong" }; // Replies with pong.
	        discord_create_message(client, event->channel_id, &params, NULL);
	}
}

int main()
{
	struct discord *client = discord_config_init("config.json"); // This function reads the JSON file, extracts the token, sets up logging, and creates the client struct.
	discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT); // For text commands.
	discord_set_on_ready(client, &on_ready); // Registers the callback.
	discord_set_on_message_create(client, &on_message);
	discord_run(client); // Connects to Discord's Gateway, authenticates with the token, and enters the asynchronous event loop (blocking until shutdown).
}

