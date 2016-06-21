#include <mruby.h>
#include <mruby/variable.h>
#include <mruby/class.h>
#include <mruby/data.h>

typedef struct {
  int id;
} mrb_thumbnail;

static mrb_thumbnail *mrb_thumbnail_wrap(mrb_state *mrb, int id);
static void mrb_thumbnail_free(mrb_state *mrb, void *p);

static const mrb_data_type mrb_thumbnail_type = {
  "mrb_thumbnail", mrb_thumbnail_free,
};

static mrb_thumbnail *mrb_thumbnail_wrap(mrb_state *mrb, int id)
{
  mrb_thumbnail *thumbnail = (mrb_thumbnail *)mrb_malloc(mrb, sizeof(mrb_thumbnail));
  thumbnail->id = id;
  return thumbnail;
}

static mrb_value mrb_thumbnail_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_int arg_id;
  mrb_thumbnail *thumbnail;

  mrb_get_args(mrb, "i", &arg_id);

  thumbnail = mrb_thumbnail_wrap(mrb, arg_id);
  if (thumbnail == NULL) {
    return self;
  }

  DATA_PTR(self) = thumbnail;
  DATA_TYPE(self) = &mrb_thumbnail_type;

  return self;
}

static void mrb_thumbnail_free(mrb_state *mrb, void *p)
{
  mrb_thumbnail *thumbnail = (mrb_thumbnail *)p;

  mrb_free(mrb, thumbnail);
}

static mrb_value
mrb_image_get_id(mrb_state *mrb, mrb_value self)
{
  mrb_thumbnail *thumbnail;

  thumbnail = mrb_get_datatype(mrb, self, &mrb_thumbnail_type);
  if (thumbnail == NULL) {
    return mrb_fixnum_value(0);
  }

  return mrb_fixnum_value(thumbnail->id);
}

static mrb_value
mrb_image_set_id(mrb_state *mrb, mrb_value self)
{
  mrb_int arg_id;
  mrb_thumbnail *thumbnail;

  mrb_get_args(mrb, "i", &arg_id);

  thumbnail = mrb_get_datatype(mrb, self, &mrb_thumbnail_type);
  if (thumbnail == NULL) {
    return self;
  }

  thumbnail->id = arg_id;

  return self;
}

void
mrb_mruby_thumbnail_gem_init(mrb_state* mrb) {
  struct RClass *module_thumbnail;
  struct RClass *class_image;

  module_thumbnail = mrb_define_module(mrb, "Thumbnail");
  class_image = mrb_define_class_under(mrb, module_thumbnail, "Image", mrb->object_class);
  MRB_SET_INSTANCE_TT(class_image, MRB_TT_DATA);

  mrb_define_method(mrb, class_image, "initialize", mrb_thumbnail_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, class_image, "id", mrb_image_get_id, MRB_ARGS_NONE());
  mrb_define_method(mrb, class_image, "id=", mrb_image_set_id, MRB_ARGS_REQ(1));
}

void
mrb_mruby_thumbnail_gem_final(mrb_state* mrb) {
  /* finalizer */
}
