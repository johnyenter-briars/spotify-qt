
extern crate reqwest;

pub mod spotify;

pub struct Spotify {
	last_auth: i64,
	current_device: String,
	settings: super::settings::SettingsManager,
	web_client: reqwest::Client
	//web_client: hyper::Client<hyper::client::HttpConnector>
}

pub struct SearchResults {
	albums: Vec<Album>,
	artists: Vec<Artist>,
	// For playlists, we need more complex information later
	playlists: Vec<serde_json::Value>,
	tracks: Vec<Track>
}

pub struct Album {
	album_group: String,
	artist: String,
	id: String,
	image: String,
	name: String,
	release_date: chrono::DateTime<chrono::Utc>
}

pub struct Artist {
	followers: i32,
	genres: Vec<String>,
	id: String,
	image: String,
	name: String,
	popularity: i32
}

pub struct Track {
	added_at: chrono::DateTime<chrono::Utc>,
	album: String,
	album_id: String,
	artist: String,
	artist_id: String,
	duration: i32,
	id: String,
	image: String,
	is_local: bool,
	name: String
}