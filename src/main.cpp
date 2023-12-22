#include <dpp/dpp.h>

#ifdef TOKEN
const std::string BOT_TOKEN = TOKEN;
#endif 

int main() {
	dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents);
 
	bot.on_log(dpp::utility::cout_logger());
 
	bot.on_slashcommand([&](const dpp::slashcommand_t& event) {
		if (event.command.get_command_name() == "slap") {
			dpp::snowflake slapee = std::get<dpp::snowflake>(event.get_parameter("slapee"));
			if(slapee == bot.me.id) {
				event.reply(dpp::message("You can't slap me, I'm unslappable!").set_flags(dpp::m_ephemeral));
			} else {
				event.reply("i slap <@" + slapee.str() + ">");
			}
		}
	});

 
	bot.on_ready([&bot](const dpp::ready_t& event) {
		/*Uncomment the following lines if you change function signatures*/ 
		// if (dpp::run_once<struct reset_bot_commands>()) {
		// 	bot.global_bulk_command_delete();
		// }
		if (dpp::run_once<struct register_bot_commands>()) {
			dpp::slashcommand slap("slap", "slap someone", bot.me.id);
			slap.add_option(
				dpp::command_option(dpp::co_user, "slapee", "the person getting slapped", true)
			);
			bot.global_command_create(slap);
		}
	});
 
	bot.start(dpp::st_wait);
}