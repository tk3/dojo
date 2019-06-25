#!/bin/sh

cat backlog.webhook.test-request.json | jq -r .issue.commented | jq . > issue.commented
cat backlog.webhook.test-request.json | jq -r .issue.created | jq . > issue.created
cat backlog.webhook.test-request.json | jq -r .issue.deleted | jq . > issue.deleted
cat backlog.webhook.test-request.json | jq -r .issue.multi_updated | jq . > issue.multi_updated
cat backlog.webhook.test-request.json | jq -r .issue.notification_added | jq . > issue.notification_added
cat backlog.webhook.test-request.json | jq -r .issue.updated | jq . > issue.updated

cat backlog.webhook.test-request.json | jq -r .wiki.created | jq . > wiki.created
cat backlog.webhook.test-request.json | jq -r .wiki.deleted | jq . > wiki.deleted
cat backlog.webhook.test-request.json | jq -r .wiki.updated | jq . > wiki.updated

cat backlog.webhook.test-request.json | jq -r .file.added | jq . > file.added
cat backlog.webhook.test-request.json | jq -r .file.deleted | jq . > file.deleted
cat backlog.webhook.test-request.json | jq -r .file.updated | jq . > file.updated

cat backlog.webhook.test-request.json | jq -r .version_control.git_pushed | jq . > version_control.git_pushed
cat backlog.webhook.test-request.json | jq -r .version_control.git_repository_created | jq . > version_control.git_repository_created
cat backlog.webhook.test-request.json | jq -r .version_control.svn_committed | jq . > version_control.svn_committed

cat backlog.webhook.test-request.json | jq -r .project.comment_added_pull_request | jq . > project.comment_added_pull_request
cat backlog.webhook.test-request.json | jq -r .project.milestone_created | jq . > project.milestone_created
cat backlog.webhook.test-request.json | jq -r .project.milestone_deleted | jq . > project.milestone_deleted
cat backlog.webhook.test-request.json | jq -r .project.milestone_updated | jq . > project.milestone_updated
cat backlog.webhook.test-request.json | jq -r .project.pull_request_added | jq . > project.pull_request_added
cat backlog.webhook.test-request.json | jq -r .project.pull_request_updated | jq . > project.pull_request_updated
cat backlog.webhook.test-request.json | jq -r .project.user_added | jq . > project.user_added
cat backlog.webhook.test-request.json | jq -r .project.user_deleted | jq . > project.user_deleted

