
test -f ./.env && source ./.env

echo "BACKLOG_URL     = $BACKLOG_URL"
echo "BACKLOG_API_KEY = $BACKLOG_API_KEY"

CURL_OPTIONS="-s"

function get_space() {
  local path="/api/v2/space"
  curl $CURL_OPTIONS $BACKLOG_URL$path?apiKey=$BACKLOG_API_KEY
}

function get_space_licence() {
  local path="/api/v2/space/licence"
  curl $CURL_OPTIONS $BACKLOG_URL$path?apiKey=$BACKLOG_API_KEY
}

function get_space_diskusage() {
  local path="/api/v2/space/diskUsage"
  curl $CURL_OPTIONS $BACKLOG_URL$path?apiKey=$BACKLOG_API_KEY
}

function get_issues() {
  local path="/api/v2/issues"
  curl $CURL_OPTIONS $BACKLOG_URL$path?apiKey=$BACKLOG_API_KEY
}

function delete_issues() {
  local path="/api/v2/issues/$1"
  curl $CURL_OPTIONS --request DELETE $BACKLOG_URL$path?apiKey=$BACKLOG_API_KEY
}

function count_issues() {
  local path="/api/v2/issues/count"
  curl $CURL_OPTIONS $BACKLOG_URL$path?apiKey=$BACKLOG_API_KEY
}

function get_issue_comments() {
  local issueIdOrKey="$1"
  local path="/api/v2/issues/$issueIdOrKey/comments"
  curl $CURL_OPTIONS $BACKLOG_URL$path?apiKey=$BACKLOG_API_KEY
}

